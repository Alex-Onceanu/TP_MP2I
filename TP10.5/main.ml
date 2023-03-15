(* Renvoie e^n mod m *)
let rec exp_rapide_mod a n m =
  if n = 0 then 1
  else if n = 1 then (a mod m)
  else if n mod 2 = 0 then (exp_rapide_mod ((a * a) mod m) (n / 2) m) mod m
  else (a * exp_rapide_mod ((a * a) mod m) (n / 2) m) mod m
;;

(* 10000000000  -> 28974 *)
let u n =
  (7 * exp_rapide_mod 15091 n 64007) mod 64007
;;

type arbre =
  | Feuille of int * int
  | Noeud of int * int * arbre * arbre (* (li, mi, g, d) *)
;;


let construit_arbre n =
  let rec squelette n = 
    if n = 0 then Feuille(0, 0)
    else Noeud(0, 0,
      squelette (u (2 * n) mod n), 
      squelette (u (2 * n + 1) mod n) )
  in let rec remplit (a : arbre) (compt : int) : arbre * int =
    match a with
    | Feuille(_, _) -> (Feuille(compt, compt), compt)
    | Noeud(_, _, g, d) -> let (arbg, suivg) = remplit g (compt + 1) in
                        let (arbd, suivd) = remplit d (suivg + 1) in
                        (Noeud(compt, suivd, arbg, arbd), suivd)
  in let (rep, _) = remplit (squelette n) 0 in rep
;;


(* Renvoie (N, F), avec N nb de noeuds, F nb de feuilles de a *)
let compte_noeuds_feuilles (a : arbre) : (int * int) =
  (* Renvoie (N, F) où N est le nb de noeuds non feuilles*)
  let rec uniq_n_f (a : arbre) : (int * int) =
    match a with
    | Feuille(_, _) -> (0, 1)
    | Noeud(_, _, g, d) -> let (ng, fg) = uniq_n_f g in
                        let (nd, fd) = uniq_n_f d in
                        (1 + ng + nd, fg + fd)
  in let (qn, f) = uniq_n_f a in (qn + f, f)
;;

