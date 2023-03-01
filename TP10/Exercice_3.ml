(* Désormais j'écrirai la signature explicite de chaque fonction *)
(* Je me suis rendu compte de leur importance à l'exercice précédent. *)

type 'a tree = Node of 'a * ('a tree list);;

(* Renvoie le plus grand élément positif de l *)
let maximum (l : 'a list) : 'a =
  (* aux renvoie le maximum de max_loc::l *)
  let rec aux (l : 'a list) (max_loc : 'a) : 'a =
    match l with
    | [] -> max_loc
    | h::t -> if h > max_loc then aux t h else aux t max_loc
  in aux l 0
;;
  
let rec hauteur (Node(x, l) : 'a tree) : int =
  1 + maximum (List.map hauteur l)
;;

(*
   5
4  2  1
     9 8
*)
let a = Node(5,
             [ Node(4,
                  []);
               Node(2, 
                  []); 
               Node(1, 
                  [ Node(9,
                        []);
                    Node(8,
                        [])
                   ]
                  )
             ]
            )
;;

let rec etiquette (Node(x, q) : 'a tree) (l:'a list) : 'a =
  match l with
  | [] -> x
  | h::t -> etiquette (List.nth q h) t
;;

let rec parcours_prefixe (Node(x, l) : 'a tree) : 'a list =
  let rec aux (Node(x, l) : 'a tree) (acc : 'a list) =
    match l with
    | [] -> acc
    | (Node (hx, hl))::t -> aux (Node(x, t)) ((aux (Node(hx, hl)) [hx]) @ acc)
  in List.rev (aux (Node(x, l)) [x])
;;

let rec parcours_postfixe (Node(x, l) : 'a tree) : 'a list =
  match l with
  | [] -> [x]
  | h::t -> (parcours_prefixe h) @ (parcours_prefixe (Node(x, t)))
;;

let liste_largeur (a : 'a tree) : 'a list =
  let rec aux (l_actuel : 'a tree list) (l_suivant : 'a tree list) : 'a list =
    match l_actuel with
    | [] -> if l_suivant = [] then [] else aux l_suivant []
    | (Node(x, l))::t -> x::(aux t (l_suivant @ l))
  in aux [a] []
;;

(* On peut enfin afficher un arbre dans le bon ordre, par étages !! 
Même si une bonne fonction d'affichage gérerait les tabulations
histoire qu'on puisse voir quel noeud est le fils de qui *)
let print_tree (a : 'a tree) : 'a list =
  let rec aux (l_actuel : 'a tree list) (l_suivant : 'a tree list) : 'a list =
    match l_actuel with
    | [] -> if l_suivant = [] then []
            else let _ = print_newline() in aux l_suivant []
    | (Node(x, l))::t -> let _ = print_string (string_of_int x ^ " ")
                                 in (aux t (l_suivant @ l))
  in aux [a] []
;;

let test() : unit =
  assert(hauteur a = 3);
  assert(hauteur (Node(1, [])) = 1);
  assert(etiquette a [2; 0] = 9);

  print_string "Fin des tests."
;;

test();;