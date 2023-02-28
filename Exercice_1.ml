
let diviseurs_stricts n =
  let rec aux n i =
    if i = n then [] 
    else if n mod i = 0 then i::(aux n (i + 1))
    else aux n (i + 1)
  in aux n 1
;;

let rec somme l =
  match l with
  | [] -> 0
  | x::q -> x + somme q
;;

let rec w n =
  if n <= 1 then 1
  else list_w n

and list_w n =
  somme (List.map w (diviseurs_stricts n))
;;

let rec produit l =
  match l with
  | [] -> 1
  | x::q -> x * (produit q)
;;

let rec range n =
  let rec aux n i acc =
    if i = n then acc
    else aux n (i + 1) (i::acc)
  in aux n 1 []
;;

let premier n =
  (List.length (diviseurs_stricts n)) = 1
;;

let p n =
  let rec aux n compt nb_prems acc =
    if nb_prems = n then acc
    else if premier compt then aux n (compt + 1) (nb_prems + 1) compt
    else aux n (compt + 1) nb_prems acc
  in aux n 1 0 0
;;

let b n =
  (w (produit(List.map p (range n))))
;;

let quelques_termes f combien =
  List.map f (range combien)
;;

let rec affiche l =
  match l with
  | [] -> ()
  | x::q -> (print_int(x);
  print_string ", ";
  affiche q)
;;

(* Expressions arithmétiques *)

type bool_expr =
	| Or of bool_expr * bool_expr
	| And of bool_expr * bool_expr
	| Not of bool_expr
	| Equal of arith_expr * arith_expr

and arith_expr =
	| Int of int
	| Variable of string
	| Add of arith_expr * arith_expr
	| Mult of arith_expr * arith_expr
	| IfTE of bool_expr * arith_expr * arith_expr
;;

type context = (string * int) list;;

let rec get_var s l =
	match l with
	| [] -> failwith "introuvable."
	| x::q -> let (a, n) = x in if a = s then n else get_var s q
;;

let eval_arith a b = true;;

let rec eval_bool e c =
	match e with
	| Or(g, d) -> (eval_bool g c) || (eval_bool d c)
	| And(g, d) -> (eval_bool g c) && (eval_bool d c)
	| Not(x) -> not (eval_bool x c)
	| Equal(g, d) -> (eval_arith g c) = (eval_arith d c)

and eval_arith e c =
	match e with
	| Int(x) -> x
	| Variable(s) -> get_var s c
	| Add(g, d) -> eval_arith g c + eval_arith d c
	| Mult(g, d) -> eval_arith g c * eval_arith d c
	| IfTE(i, t, e) -> if eval_bool i c then eval_arith t c else eval_arith e c
;;


let test() =
  assert(w 6 = 3);
  
  (* les nombres de Bell ordonnés *)
  affiche (quelques_termes b 10);
  
  (* (4 + 9) * n avec n = ((1 + 1) = 3) || ((4 = foo) && (2 = 2)) ? bar : 86 vaut -13 *)
  let tmp = Mult(
  	Add(Int(4), Int(9)), IfTE(
  		Or(
  			Equal(Add(Int(1), Int(1)), Int(3)), And(
  				Equal(Int(4), Variable("foo")), Equal(Int(2), Int(2))
  				)
  			), 
  		Variable("bar"), Int(86))
  	) in assert (eval_arith tmp [("foo", 4); ("bar", -1)] = -13);

  print_string "\nFin des tests.\n";
;;

test();;