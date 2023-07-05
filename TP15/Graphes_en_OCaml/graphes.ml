type graphe = int list array

(* 0 <-> 1 <-> 3 <-> 2
   4 <-> 5 *)
let g0 : graphe = [| [ 1 ]; [ 0; 3 ]; [ 3 ]; [ 1; 2 ]; [ 5 ]; [ 4 ] |]

let nb_aretes (g : graphe) : int =
  Array.fold_left (fun a b -> a + b) 0 (Array.map (fun l -> List.length l) g)
;;

(* Un graphe non-orienté G = (S, A) vérifie nécessairement "2 | card A" *)
let nb_aretes_no (g : graphe) : int = nb_aretes g / 2

let rec liste_composante_connexe (g : graphe) (v : bool array) (s : int) :
    int list =
  if not v.(s) then begin
    v.(s) <- true;
    s :: List.flatten (List.map (liste_composante_connexe g v) g.(s))
  end
  else []
;;

(* Renvoie la liste des composantes connexes de g *)
let composantes_connexes (g : graphe) : int list list =
  let n = Array.length g in
  let vu = Array.make n false in
  let cc = ref [] in
  for i = 0 to n - 1 do
    if not vu.(i) then cc := liste_composante_connexe g vu i :: !cc
  done;
  !cc
;;

(* ___fonctions auxiliaires pour bipartition___ *)
(* J'ai utilisé des vraies couleurs pour rendre l'algo bien lisible *)
(* Il va de soi qu'utiliser des int "0 = aucun, 1 = Noir, 2 = Rouge" revient au même
   Et permettrait de généraliser l'algo de coloriage à plus de 2 couleurs *)

type couleur = Noir | Rouge | Aucun

let change (c : couleur) : couleur =
  match c with
  | Noir -> Rouge
  | Rouge -> Noir
  | Aucun -> Aucun
;;

let choix (a : 'a option) (b : 'a option) =
  match (a, b) with
  | None, None -> None
  | Some v, None | None, Some v -> None
  | Some u, Some v -> Some u
;;

let to_bool (c : couleur) : bool =
  match c with
  | Noir -> true
  | Rouge -> false
  | Aucun -> failwith "La couleur \"Aucun\" ne peut pas être convertie en bool"
;;

(* Renvoie None si la bipartition d'une composante connexe est impossible, () sinon *)
(* Effet de bord : change l'état de tab_couleurs car colorie les sommets petit à petit *)
let rec bipartition_composante (g : graphe) (tab_couleurs : couleur array)
    (c : couleur) (sommet : int) : unit option =
  if tab_couleurs.(sommet) != Aucun then
    if tab_couleurs.(sommet) = c then Some () else None
  else begin
    tab_couleurs.(sommet) <- c;
    List.fold_left choix (Some ())
      (List.map (bipartition_composante g tab_couleurs (change c)) g.(sommet))
  end
;;

(* Appelle simplement la bipartition d'une composante connexe sur toutes les composantes connexes
   et vérifie que le résultat n'est jamais None *)
let bipartition (g : graphe) : bool array option =
  let couleurs = Array.make (Array.length g) Aucun in
  if
    Option.is_none
      (List.fold_left choix (Some ())
         (List.map
            (fun l -> bipartition_composante g couleurs Rouge (List.hd l))
            (composantes_connexes g)))
  then None
  else Some (Array.map to_bool couleurs)
;;

let test () =
  assert (composantes_connexes g0 = [ [ 4; 5 ]; [ 0; 1; 3; 2 ] ]);
  assert (bipartition g0 = Some [| false; true; true; false; false; true |])
(* Tout est bon normalement ! *)
;;

test ()
