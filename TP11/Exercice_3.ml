type couleur = Rouge | Noir

type 'a noeud_arn =
  | Feuille of 'a
  | Noeud of couleur * 'a * 'a noeud_arn * 'a noeud_arn

let couleur_noeud (a : 'a noeud_arn) : couleur =
  match a with
  | Feuille c | Noeud (c, _, _, _) -> c
;;

let double_rouge (a : 'a noeud_arn) : bool =
  let rec aux (a : 'a noeud_arn) (couleur_pere : couleur) =
    match a with
    | Feuille c -> c = Rouge && c = couleur_pere
    | Noeud (c, v, g, d) ->
        (c = Rouge && couleur_pere = c) || aux g c || aux d c
  in
  aux a Noir
;;

exception ErreurHauteurNoire

type 'a arn = 'a noeud_arn option
