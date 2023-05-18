type couleur = Rouge | Noir

(* Noeud d'un arbre Rouge-Noir *)
type 'a noeud_arn =
  | Feuille of 'a
  | Noeud of couleur * 'a * 'a noeud_arn * 'a noeud_arn

exception ErreurHauteurNoire

(* Renvoie la couleur d'un noeud d'ARN *)
let couleur_noeud (a : 'a noeud_arn) : couleur =
  match a with
  | Feuille _ -> Noir
  | Noeud (c, _, _, _) -> c
;;

(* Renvoie l'étiquette d'un noeud ou d'une feuille d'ARN (les deux en ont une) *)
let etiquette_noeud (a : 'a noeud_arn) : 'a =
  match a with
  | Feuille v | Noeud (_, v, _, _) -> v
;;

(* true si a contient un doublon de noeuds rouges, false sinon *)
let double_rouge (a : 'a noeud_arn) : bool =
  let rec aux (a : 'a noeud_arn) (couleur_pere : couleur) =
    match a with
    | Feuille c -> false
    | Noeud (c, v, g, d) ->
        (c = Rouge && couleur_pere = c) || aux g c || aux d c
  in
  aux a Noir
;;

(* Renvoie la hauteur noire d'un arn supposé correct. *)
(* S'il n'est pas correct lève l'erreur ErreurHauteurNoire *)
let rec bh (a : 'a noeud_arn) : int =
  match a with
  | Feuille c -> 1
  | Noeud (c, v, g, d) ->
      let bh_g, bh_d = (bh g, bh d) in
      if bh_g = bh_d then bh_g + if c = Noir then 1 else 0
      else raise ErreurHauteurNoire
;;

(* true si a est relaxé, false sinon. *)
let est_relax (a : 'a noeud_arn) : bool =
  try (not (double_rouge a)) && bh a >= 0 with
  | ErreurHauteurNoire -> false
  | _ -> failwith "vrai erreur"
;;

(* Corrige arb, de sorte à ce qu'il soit relaxé *)
let rec correctionARN (arb : 'a noeud_arn) : 'a noeud_arn =
  match arb with
  | Feuille v -> Feuille v
  | Noeud (Noir, z, Noeud (Rouge, y, Noeud (Rouge, x, a, b), c), d)
  | Noeud (Noir, z, Noeud (Rouge, x, a, Noeud (Rouge, y, b, c)), d)
  | Noeud (Noir, x, a, Noeud (Rouge, z, Noeud (Rouge, y, b, c), d))
  | Noeud (Noir, x, a, Noeud (Rouge, y, b, Noeud (Rouge, z, c, d))) ->
      Noeud (Rouge, y, Noeud (Noir, x, a, b), Noeud (Noir, z, c, d))
  | _ -> arb
;;

(* Insère l'élément x dans l'arbre a, en faisant en sorte que a reste relaxé *)
let rec insertARNrelax (x : 'a) (a : 'a noeud_arn) : 'a noeud_arn =
  match a with
  | Feuille v when x < v -> Noeud (Rouge, x, Feuille x, Feuille v)
  | Feuille v when x > v -> Noeud (Rouge, v, Feuille v, Feuille x)
  | Noeud (c, v, g, d) when x > v ->
      correctionARN (Noeud (c, v, g, insertARNrelax x d))
  | Noeud (c, v, g, d) when x < v ->
      correctionARN (Noeud (c, v, insertARNrelax x g, d))
  | _ -> a
;;

(* Renvoie le nombre de noeuds + nombre de feuilles de a *)
let rec taille (a : 'a noeud_arn) : int =
  match a with
  | Feuille _ -> 1
  | Noeud (c, v, g, d) -> 1 + taille g + taille d
;;

(* Renvoie la hauteur (feuilles et noeuds compris) d'un arn (à partir de sa racine) *)
let rec hauteur (a : 'a noeud_arn) : int =
  match a with
  | Feuille _ -> 0
  | Noeud (c, v, g, d) -> 1 + max (hauteur g) (hauteur d)
;;

type 'a arn = 'a noeud_arn option

(* Renvoie la couleur de la racine d'un arn a *)
let couleur_racine (a : 'a arn) : couleur option =
  match a with
  | None -> None
  | Some x -> Some (couleur_noeud x)
;;

(* Renvoie true ssi l'arn a contient un doublon de noeuds rouges *)
let double_rouge_arn (a : 'a arn) : bool =
  match a with
  | None -> false
  | Some x -> double_rouge x
;;

(* Renvoie la hauteur noire d'un arn *)
let bh_arn (a : 'a arn) : int option =
  match a with
  | None -> None
  | Some x -> Some (bh x)
;;

(* Vérifie que a est bien un ARN *)
let est_correct (a : 'a arn) : bool =
  try
    (not (double_rouge_arn a))
    && couleur_racine a = Some Noir
    && bh_arn a > None
  with
  | ErreurHauteurNoire -> false
  | _ -> failwith "vrai erreur"
;;

(* Renvoie le même arbre, mais dont la racine est de la couleur c *)
let colorieARN (a : 'a noeud_arn) (c : couleur) : 'a noeud_arn =
  match a with
  | Feuille v -> Feuille v
  | Noeud (_, v, g, d) -> Noeud (c, v, g, d)
;;

(* Insère un élément x dans un arn a *)
(* O(log2(n)) *)
let insertionARN (x : 'a) (a : 'a arn) : 'a arn =
  match a with
  | None -> None
  | Some r ->
      let j = insertARNrelax x r in
      Some (colorieARN j Noir)
;;

(* Renvoie un élément de la suite b n *)
let rec b (n : int) : 'a arn =
  if n = 0 then Some (Feuille 0) else insertionARN n (b (n - 1))
;;

(* Renvoie la liste des b n *)
let rec suite_b (n : int) : 'a arn list =
  if n = 0 then [ b 0 ] else b n :: suite_b (n - 1)
;;

(* Renvoie le temps en s mis pour la création d'un b n *)
let time_arn (n : int) : float =
  let debut = Sys.time () in
  let _ = b n in
  Sys.time () -. debut
;;

(* Renvoie le temps en s mis pour une insertionARN *)
let time_insertion_arn (v : 'a) (a : 'a arn) : float =
  let debut = Sys.time () in
  let _ = insertionARN v a in
  Sys.time () -. debut
;;

(* Renvoie des temps d'exécution de b n pour différentes valeurs de n *)
(* Donc pour tous les n compris dans [n_min, n_max] tous les pas *)
let rec tableau_time_arn (n_min : int) (n_max : int) (pas : int) : float list =
  if n_min > n_max then []
  else time_arn n_min :: tableau_time_arn (n_min + pas) n_max pas
;;

(* Vérifie que l'hauteur de a est inférieure à 2 * log2(2 * n + 1) *)
(* où n est le nombre d'éléments stockés dans a *)
let bon_equilibre (a : 'a arn) : bool =
  match a with
  | None -> false
  | Some x ->
      float_of_int (hauteur x) <= 2.0 *. log (float_of_int (taille x) /. log 2.0)
;;

(* Insere tous les elements de l dans un arbre a *)
(* O(n * log(n)) où n est le nombre d'éléments dans la liste + dans a *)
let insertion_liste (l : 'a list) (a : 'a arn) =
  List.fold_right (fun x y -> insertionARN x y) l a
;;

(* Renvoie une liste contenant toutes les feuilles d'un arn par ordre croissant *)
(* O(n) *)
let listerARN (a : 'a arn) : 'a list =
  let rec aux (n : 'a noeud_arn) (l : 'a list) : 'a list =
    match n with
    | Feuille v -> v :: l
    | Noeud (c, v, g, d) -> aux d (aux g l)
  in
  match a with
  | None -> []
  | Some n -> List.rev (aux n [])
;;

(* Fonction de tri en O(n * log(n)) car insertion_liste insere n objets *)
(* avec une complexité en O(log(n)) pour chaque insertion. Donc n * log(n).*)
(* Et listerARN est en O(n) donc on reste sur du O(n * log(n)) *)
let tri_arn (l : 'a list) : 'a list =
  match l with
  | [] -> []
  | x :: q -> listerARN (insertion_liste q (Some (Feuille x)))
;;

(* Renvoie le plus petit élément de a *)
let min_ARN (a : 'a arn) : 'a option =
  let rec aux (a : 'a noeud_arn) : 'a =
    match a with
    | Feuille v -> v
    | Noeud (c, v, g, d) -> aux g
  in
  match a with
  | None -> None
  | Some x -> Some (aux x)
;;

(* Renvoie tous les éléments de t compris dans [a, b] *)
let query_range (a : 'a) (b : 'b) (t : 'a arn) : 'a list =
  let rec aux (a : 'a) (b : 'b) (t : 'a noeud_arn) : 'a list =
    match t with
    | Feuille v -> if v <= b && v >= a then [ v ] else []
    | Noeud (c, v, g, d) ->
        if v < a then aux a b d
        else if v > b then aux a b g
        else aux a b g @ aux a b d
  in
  match t with
  | None -> []
  | Some x -> aux a b x
;;

let test () =
  assert (est_correct (b 300));
  assert (bon_equilibre (b 300));
  assert (tri_arn [ 7; 6; 2; 3; 5; 4; 9; 0; 8 ] = [ 0; 2; 3; 4; 5; 6; 7; 8; 9 ]);
  assert (query_range 3 5 (b 100) = [ 3; 4; 5 ]);

  print_string "Le programme est correct.\n"
;;

(*
Suppression : voilà l'idée, il reste à traiter les différents cas de la correction 
En faisant exactement la même chose que pour l'insertion (donc un énorme match with)
On fait remonter le problème (ici lié à la hauteur noire plutôt qu'aux doublons rouges)
Enfin on utilise cette fonction de correction pour supprimer un noeud et corriger les anomalies.

   (* On traite chacun des cas à la main... C'est en O(1) *)
   let correction2 (a : 'a noeud_arn) : 'a noeud_arn =
     match a with
     | Feuille _ -> a
     | Noeud (...) -> ...
     | Noeud(...) -> ...
     | Noeud(...) -> ...
     | Noeud(...) -> ...
     | Noeud (...) -> ...
     | Noeud(...) -> ...
     | Noeud(...) -> ...
     | Noeud(...) -> ...
   ;;

   let suppressionARN (x : 'a) (a : 'a arn) : 'a arn =
     let rec aux (x : 'a) (n : 'a noeud_arn) : 'a noeud_arn =
       match n with
       | Feuille _ -> failwith "non défini"
       | Noeud (c, v, Feuille _, d) -> d
       | Noeud (c, v, g, Feuille _) -> g
       | Noeud (c, v, g, d) when x <= v -> correction2 (Noeud (c, v, aux x g, d))
       | Noeud (c, v, g, d) when x > v -> correction2 (Noeud (c, v, g, aux x d))
       | _ -> failwith "???"
     in
     match a with
     | None -> None
     | Some noeud -> Some (aux x noeud)
   ;;
*)
