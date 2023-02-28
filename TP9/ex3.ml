type couleur = Coeur | Pique | Carreau | Trefle ;;

let couleur1 = Pique ;;

(* Détermine si c est une couleur rouge (coeur ou carreau) *)
let est_rouge (c:couleur) : bool = match c with
	| Coeur   -> true
	| Carreau -> true
	| Pique   -> false
	| Trefle  -> false ;;

assert (est_rouge Carreau);; (* vaut true *)

type carte = 
	| Nombre of (int * couleur) (* Cartes 2 à 10 *)
	| Valet of couleur
	| Dame of couleur
	| Roi of couleur
	| As of couleur ;;

let carte_1 = Valet Coeur ;;
let carte_2 = Nombre (9, Pique) ;;

(* Renvoie la couleur de ca *)
let couleur_de_carte (ca:carte) : couleur = match ca with
	| Nombre (n, cou) -> cou 
	| Valet cou -> cou
	| Dame cou -> cou
	| Roi cou -> cou
	| As cou -> cou ;;


assert (couleur_de_carte (Roi Trefle) = Trefle) ;;

(* ______________________________________________________________ *)

let string_of_couleur c =
	match c with
	| Coeur -> "cœur"
	| Carreau -> "carreau"
	| Pique -> "pique"
	| Trefle -> "trefle"
;;

let string_of_carte c =
	let nom_of_carte c =
		match c with
		| Nombre(v, _) -> string_of_int v
		| Valet _ -> "Valet"
		| Dame _ -> "Dame"
		| Roi _ -> "Roi"
		| As _ -> "As"
	in nom_of_carte c ^ " de " ^ string_of_couleur (couleur_de_carte c)
;;

(* On remarque que les cartes sont ordonnées par ordre lexicographique :
D'abord vient leur constructeur (par ordre d'apparition dans le code,
puis les paramètres dans l'ordre d'apparition aussi. *)

let relation_ordre (a:carte) (b:carte) : bool =
	(couleur_de_carte a, a) <= (couleur_de_carte b, b)
;;

assert(relation_ordre (Nombre (3, Coeur)) (Roi Trefle));;
assert((As Coeur) <= (As Trefle));;

let rec inserer (c : carte) (l : carte list) =
	match l with
	| [] -> [c]
	| h::t -> if (relation_ordre c h) then c::h::t else (h::(inserer c t))
;;

let tri_insertion l =
	let rec accumulation l2 acc =
		match l2 with 
		| [] -> acc
		| h::t -> accumulation t (inserer h acc)
	in accumulation l []
;;

let gen_couleur (c : couleur) = 
	let rec cartes_suivantes (c : couleur) (i : int) (acc : carte list) =
		if i > 13 then acc
		else match i with
		| 1 -> cartes_suivantes c (i + 1) (As c::acc)
		| 11 -> cartes_suivantes c (i + 1) (Valet c::acc)
		| 12 -> cartes_suivantes c (i + 1) (Dame c::acc)
		| 13 -> cartes_suivantes c (i + 1) (Roi c::acc)
		| _ -> cartes_suivantes c (i + 1) (Nombre(i, c)::acc)
	
	in cartes_suivantes c 1 []
;;

let deal (l : carte list) : (carte list * carte list) =
  let rec remplit_mains l (i : int) (a : carte list) (b : carte list) =
    match l with
    | [] -> (a, b)
    | h::t -> if i mod 2 = 0 then remplit_mains t (i + 1) (inserer h a) (b)
    else remplit_mains t (i + 1) (a) (inserer h b)
  in remplit_mains l 0 [] []
;;

let deck = (gen_couleur Coeur) @ (gen_couleur Carreau) @ (gen_couleur Pique) @ (gen_couleur Trefle) in deal deck;;

let test() =
	assert(inserer(Valet Carreau) [(Roi Coeur) ; (Nombre (4, Carreau)); (Nombre (1, Trefle))]
		= [(Roi Coeur) ; (Nombre (4, Carreau)); (Valet Carreau); (Nombre (1, Trefle))]);

  assert(tri_insertion (gen_couleur Coeur) = [Nombre (2, Coeur); Nombre (3, Coeur); Nombre (4, Coeur); Nombre (5, Coeur);
    Nombre (6, Coeur); Nombre (7, Coeur); Nombre (8, Coeur); Nombre (9, Coeur);
    Nombre (10, Coeur); Valet Coeur; Dame Coeur; Roi Coeur; As Coeur]);
	


	print_string "Tous les tests ont reussi.";
;;
