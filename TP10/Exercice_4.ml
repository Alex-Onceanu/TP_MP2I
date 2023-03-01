let int_of_bool b = if b then 1 else 0;;

let cherche_plus_long (l : string list) : string =
  let rec aux (l : string list) (max_len : int) (res : string) : string =
    match l with
    | [] -> res
    | h::t -> let tmp = String.length h in (
                if tmp > max_len then aux t tmp h
                else aux t max_len res)
  in aux l 0 ""
;;

(* _______________________________________________________________*)

type pre_tree = Node of (bool * (char * pre_tree) list);;

let t = Node(false, [
        ('t', Node(true, [
          ('r', Node(false, [
            ('o', Node(true, [])) 
          ]))
        ]));
        ('f', Node(false, [
          ('o', Node(true, []))
        ]))
]);;

(* Il suffit de compter le nombre de noeuds 'V' *)
let rec taille (Node(b, l) : pre_tree) : int =
  match l with
  | [] -> int_of_bool b
  | (c, a)::t -> taille a + taille (Node(b, t))
;;

let liste_tous_les_mots (arb : pre_tree) : string list =
    let rec aux (Node(b, l) : pre_tree) (actuel : char list) : string list =
      match l with
      | [] -> if b then [String.of_seq(List.to_seq (List.rev actuel))] else []
      | (c, a)::t -> aux a (c::actuel) @ aux (Node(b, t)) actuel
    in aux arb []
;;

let plus_long (a : pre_tree) : int =
  String.length (cherche_plus_long (liste_tous_les_mots a))
;;

let rechercher (s : string) (a : pre_tree) : bool =
  List.mem s (liste_tous_les_mots a)
;;

(* Renvoie un pre_tree de type "colonne" formant comme unique mot s *)
let rec tree_of_string (s : string) : pre_tree =
  if String.length s = 0 then Node(true, [])
  else Node(false, [(s.[0], tree_of_string (String.sub s 1 (String.length s - 1)))])
;;

let ajouter (s : string) (Node(arbb, arbl) : pre_tree) : pre_tree =
  (* ajoute s à une liste d'aretes de pre_tree *)
  let rec aux (s : string) (l : (char * pre_tree) list) : (char * pre_tree) list =
    if String.length s = 0 then []
    else (let suiv = String.sub s 1 (String.length s - 1) in (
    match l with
    | [] -> [(s.[0], tree_of_string suiv)]
    | (c, Node(ab, al))::t -> if c = s.[0] then (c, Node(ab, aux suiv al))::t
                              else (c, Node(ab, al))::(aux s t) ))
  in Node(arbb, aux s arbl)
;;

let test() =
  assert(taille t = 3);
  assert(plus_long t = 3);
  assert(rechercher "fo" t);
  assert(liste_tous_les_mots (ajouter "fils" t) = ["tro"; "t"; "fo"; "fils"]);

  print_string "Fin des tests.";
;;

test();;