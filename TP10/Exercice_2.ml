type 'a ab =
  | V
  | N of 'a * 'a ab * 'a ab
;;

let max a b = if a > b then a else b;;

let rec hauteur a =
	match a with
	| V -> -1
	| N(v, g, d) -> 1 + max (hauteur g) (hauteur d)
;;

let rec taille a =
	match a with
	| V -> 0
	| N (v, g, d) -> 1 + taille g + taille d
;;


let rec etiquette a l =
	match a with
	| V -> failwith "Un arbre vide n'a pas d'étiquette."
	| N(v, g, d) -> (match l with
									| [] -> v
									| x::q -> if x then etiquette d q
														else etiquette g q)
;;

let rec est_miroir a b =
	match (a, b) with
	| (V, V) -> true
	| (N(av, ag, ad), N(bv, bg, bd)) -> est_miroir ag bd && est_miroir ad bg
	| _ -> false
;;

let rec miroir a =
	match a with
	| V -> V
	| N(v, g, d) -> N(v, miroir d, miroir g)
;;

let est_symetrique a = est_miroir a a;;


(* Fonctions avec @ : *)

(*
let rec liste_prefixe a =
	match a with
	| V -> []
	| N(v, g, d) -> v::((liste_prefixe g) @ (liste_prefixe d))
;;


let rec liste_infixe a =
	match a with
	| V -> []
	| N(v, g, d) -> (liste_infixe g) @ (v::(liste_infixe d))
;;

let rec liste_postfixe a =
	match a with
	| V -> []
	| N(v, g, d) -> (liste_postfixe g) @ (liste_postfixe d) @ [v]
;;
*)

let rec liste_prefixe a =
	let rec aux a acc =
		match a with
		| V -> acc
		| N(v, g, d) -> aux d (aux g (v::acc))
	in List.rev (aux a [])
;;

let rec liste_infixe a =
	let rec aux a acc =
		match a with
		| V -> acc
		| N(v, g, d) -> aux d (v::(aux g acc))
	in List.rev (aux a [])
;;

let rec liste_postfixe a =
	let rec aux a acc =
		match a with
		| V -> acc
		| N(v, g, d) -> aux g (aux d (v::acc))
	in aux a []
;;

let rec tree_map f a =
	match a with
	| V -> V
	| N(v, g, d) -> N(f v, tree_map f g, tree_map f d)
;;

(* Arnaque, mais ces deux fonctions conviennent
let tree_sum a = List.fold_left (fun x y -> x + y) 0 (liste_infixe a);;
let appartient v a = List.mem v (liste_infixe a);;
*)

let rec tree_sum a =
	match a with
	| V -> 0
	| N(v, g, d) -> v + tree_sum g + tree_sum d
;;

let rec appartient x a =
	match a with
	| V -> false
	| N(v, g, d) -> if v = x then true
									else (appartient x g) || (appartient x d)
;;

let rec tree_fold (f : 'a -> 'b -> 'b -> 'c) (a : 'a ab) (seed : 'c) : 'c =
	match a with
	| V -> seed
	| N(v, g, d) -> f v (tree_fold f g seed) (tree_fold f d seed)
;;

(* Pour vérifier que la fonction tree_fold est bonne *)
let tree_sum2 a = tree_fold (fun v g d -> v + g + d) a 0;;
let appartient2 x a = 
	tree_fold (fun v g d -> if v = x then true else (g || d)) a false
;;


let a = N(4, N(3, N(1, V, V), V), N(3, V, N(1, V, V)));;

let test() =
	assert(est_symetrique a);
	assert(liste_infixe a = [1; 3; 4; 3; 1]);

	assert((tree_sum a) = 12 && (tree_sum2 a) = 12);
	assert((appartient 4 a) && (appartient2 4 a));
	

	print_string "Fin des tests."
;;

test();;