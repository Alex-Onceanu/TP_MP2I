type formule =
  | Var of string
  | Top
  | Bot
  | And of formule * formule
  | Or of formule * formule
  | Not of formule

let implique (f1, f2) = Or (Not f1, f2)
let equivalence (f1, f2) = Or (And (f1, f2), And (Not f1, Not f2))

(*** PARSER ***)

(* Symboles:
   'T' -> top
   'F' -> bot
   '&' -> And
   '|' -> Or
   '~' -> Not
   '>' -> implication
   '=' -> equivalence
*)

(* Détermine si c correspond à un opérateur binaire logique *)
let is_binop (c : char) : bool =
  match c with
  | '&' | '|' | '>' | '=' -> true
  | _ -> false
;;

(* Priorité de chaque opérateur. Permet de déterminer
   comment interpréter une formule sans parenthèses.
   Par exemple, "x&y|z" sera interprété comme "(x&y)|z"
   car & est plus prioritaire que | *)
let priority (c : char) : int =
  match c with
  | '&' -> 4
  | '|' -> 3
  | '=' -> 2
  | '>' -> 1
  | _ -> 5
;;

(* indice de l'opérateur le moins prioritaire parmis ceux
   qui ne sont pas entre parenthèses entre s.[i] et s.[j]
   inclus *)
let find_op_surface (s : string) (i : int) (j : int) : int =
  (* k: indice actuel
     res: indice du meilleur résultat jusqu'ici
     paren_lvl: niveau d'imbrication des parenthèses actuel *)
  let rec aux (k : int) (res : int) (paren_lvl : int) : int =
    if k = j + 1 then res
    else if s.[k] = '(' then aux (k + 1) res (paren_lvl + 1)
    else if s.[k] = ')' then aux (k + 1) res (paren_lvl - 1)
      (* Le caractère lu est pris si l'on est hors des parenthèses,
         que le caractère est bien un opérateur, et qu'il est moins
         prioritaire que le meilleur résultat jusqu'ici *)
    else if
      paren_lvl = 0
      && is_binop s.[k]
      && (res = -1 || priority s.[k] < priority s.[res])
    then aux (k + 1) k paren_lvl
    else aux (k + 1) res paren_lvl
  in
  aux i (-1) 0
;;

(* Lit la chaîne de caractère s et la transforme en formule *)
let parse (s : string) : formule =
  let n = String.length s in
  let rec parse_aux (i : int) (j : int) =
    assert (i < n && j < n && i <= j);
    if s.[i] = ' ' then parse_aux (i + 1) j
    else if s.[j] = ' ' then parse_aux i (j - 1)
    else
      let k = find_op_surface s i j in
      if k = -1 then
        if s.[i] = '~' then Not (parse_aux (i + 1) j)
        else if s.[i] = '(' then
          if s.[j] != ')' then (
            print_int j;
            failwith "Mauvais parenthésage")
          else parse_aux (i + 1) (j - 1)
        else if i = j && s.[i] = 'T' then Top
        else if i = j && s.[i] = 'F' then Bot
        else Var (String.sub s i (j - i + 1))
      else
        match s.[k] with
        | '&' -> And (parse_aux i (k - 1), parse_aux (k + 1) j)
        | '|' -> Or (parse_aux i (k - 1), parse_aux (k + 1) j)
        | '=' -> equivalence (parse_aux i (k - 1), parse_aux (k + 1) j)
        | '>' -> implique (parse_aux i (k - 1), parse_aux (k + 1) j)
        | _ -> failwith "should not happen: not an operator"
  in
  parse_aux 0 (String.length s - 1)
;;

let test_parse () =
  assert (parse "a | (b & ~c)" = Or (Var "a", And (Var "b", Not (Var "c"))));

  assert (parse "T" = Top);

  assert (
    parse "T | d > a & c" = Or (Not (Or (Top, Var "d")), And (Var "a", Var "c")));
  print_string "Tests OK\n"
;;

let s = " (J'ai faim > Je mange) & (Il est midi > J'ai faim) & (Il est midi)"
let f = parse s

let rec op_count (f : formule) : int =
  match f with
  | And (a, b) | Or (a, b) -> 1 + op_count a + op_count b
  | Not x -> 1 + op_count x
  | _ -> 0
;;

let rec est_str_triee (l : 'a list) : bool =
  match l with
  | [] -> true
  | x :: [] -> true
  | a :: b :: q -> a < b && est_str_triee (b :: q)
;;

let rec union (l1 : 'a list) (l2 : 'a list) : 'a list =
  match (l1, l2) with
  | [], [] -> []
  | x :: q, [] | [], x :: q -> x :: q
  | x1 :: q1, x2 :: q2 ->
      if x1 < x2 then x1 :: union q1 l2
      else if x2 < x1 then x2 :: union l1 q2
      else x1 :: union q1 q2
;;

let supp_doublons (l : 'a list) : 'a list =
	let rec aux (l : 'a list) (acc : 'a list) : 'a list =
		match l with
		| [] -> acc
		| x::q -> if (List.mem x acc) then aux q else x::(aux q)
	in aux l []
;;

let liste_var (f : formule) : string list =
  let rec aux f = 
  	match f with
  	| Var s -> [ s ]
  	| And (a, b) | Or (a, b) -> aux a @ aux b
  	| Not a -> aux a
  	| _ -> []
  in supp_doublons (aux f)
;;

type valuation = (string * bool) list;;

let rec interpretation (f : formule) (sigma : valuation) : bool =
  match f with 
  | Var s -> List.assoc s sigma
  | And(a, b) -> (interpretation a sigma) && (interpretation b sigma)
  | Or(a, b) -> (interpretation a sigma) || (interpretation b sigma) 
  | Not a -> not (interpretation a sigma)
  | Top -> true
  | Bot -> false
;;

let rec add_one (l : bool list) : bool list =
	match l with
	| [] -> [true]
	| x::q -> if x then false::(add_one q) else true::q
;;

let valuation_next (v : valuation) : (valuation option) =
	let s = add_one (List.map snd v) in
	if List.for_all snd v then None
	else Some (List.combine (List.map fst v) s)
;;

let valuation_init (l : string list) : valuation =
	List.combine l (List.init (List.length l) (fun n -> false))
;;


type sat_result =
| Sat of valuation
| Unsat
;;


let satsolver (f : formule) : sat_result =
	let rec aux (f : formule) (sigma : valuation option) =
		match sigma with
		| None -> Unsat
		| Some v -> if interpretation f v then Sat v else aux f (valuation_next v)
	
	in aux f (Some (valuation_init (liste_var f)))
;;


let p = And (Not (Var "mu"), Or (Top, Var "x"));;

let test () : unit =
  assert (op_count p = 3);
  
  assert (est_str_triee [ 2; 3; 5; 7; 9; 12 ]);
  assert (
    union [ 1; 3; 5; 7; 8 ] [ 0; 2; 4; 6; 9 ] = [ 0; 1; 2; 3; 4; 5; 6; 7; 8; 9 ]);
  assert (liste_var p = [ "mu"; "x" ]);
  
  assert((interpretation p [("mu", true); ("x", false)]) = false);
  
  assert (valuation_next [("x", true); ("y", true); ("z", true)] = None);

  print_string "Tout est bon.\n";
;;
