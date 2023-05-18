(* 'k est le type des clés, 'v celui des valeurs *)
type ('k, 'v) abr = V | N of 'k * 'v * ('k, 'v) abr * ('k, 'v) abr

(* Renvoie la valeur associée à la clé key *)
let rec get (key : 'k) (a : ('k, 'v) abr) : 'v option =
  match a with
  | V -> None
  | N (c, v, g, d) ->
      if key = c then Some v else if key < c then get key g else get key d
;;

(* La valeur associée à la clé key devient value *)
let rec set (key : 'k) (value : 'v) (a : ('k, 'v) abr) : ('k, 'v) abr =
  match a with
  | V -> V
  | N (c, v, g, d) ->
      if key = c then N (c, value, g, d)
      else if key < c then N (c, v, set key value g, d)
      else N (c, v, g, set key value d)
;;

(* Renvoie le même arbre sauf son élément dont la clé est minimale *)
let rec extract_min (a : ('k, 'v) abr) : ('k * 'v) * ('k, 'v) abr =
  match a with
  | V -> failwith "Extraction sur feuille impossible"
  | N (c, v, V, d) -> ((c, v), V)
  | N (c, v, g, d) -> extract_min g
;;

(* Suppression pour les ABR *)
let rec del (key : 'k) (a : ('k, 'v) abr) : ('k, 'v) abr =
  match a with
  | V -> failwith "clé manquante"
  | N (c, v, g, d) ->
      if c = key then
        let (ac, av), arb = extract_min d in
        N (ac, av, g, arb)
      else if c < key then N (c, v, del key g, d)
      else N (c, v, g, del key d)
;;

(* Ajoute un couple (key, value) à l'abr a *)
let rec ajouter (a : ('k, 'v) abr) (key : 'k) (value : 'v) : ('k, 'v) abr =
  match a with
  | V -> N (key, value, V, V)
  | N (c, v, g, d) ->
      if key < c then N (c, v, ajouter g key value, d)
      else if key > c then N (c, v, g, ajouter d key value)
      else set key value a
;;

(* Renvoie le n-ième terme de la suite des a n *)
let rec genere_a (n : int) : (int, unit) abr =
  if n = 0 then V else ajouter (genere_a (n - 1)) n ()
;;

(* Renvoie le temps en s mis pour la création de a n *)
let time_abr (n : int) : float =
  let debut = Sys.time () in
  let _ = genere_a n in
  Sys.time () -. debut
;;

(* Renvoie le temps en s mis pour un ajout dans un ABR *)
let time_insertion_abr (v : 'a) (a : (int, unit) abr) : float =
  let debut = Sys.time () in
  let _ = ajouter a v () in
  Sys.time () -. debut
;;

(* Exécuter "graphe.py" pour la courbe tracée *)
let rec tableau_time_abr (n_min : int) (n_max : int) (pas : int) : float list =
  if n_min > n_max then []
  else time_abr n_min :: tableau_time_abr (n_min + pas) n_max pas
;;

(* La fonction test ci-dessous a été écrite par ChatGPT.
   (après avoir réussi à lui faire comprendre comment fonctionne la structure...)
   J'ai vérifié que les tests sont pertinents, et ils sont plutôt réussis je trouve !
   Si cela pose un problème que je demande à ChatGPT d'écrire mes tests, dites-le-moi et j'arrêterai.*)
let test () =
  (* Test de la fonction get *)
  let abr1 = N (1, "a", V, V) in
  assert (get 1 abr1 = Some "a");
  assert (get 2 abr1 = None);

  let abr2 = N (2, "b", V, abr1) in
  let abr3 = N (3, "c", abr2, V) in
  assert (get 2 abr3 = Some "b");
  assert (get 3 abr3 = Some "c");
  assert (get 4 abr3 = None);

  (* Test de la fonction set *)
  let abr4 = set 2 "d" abr3 in
  assert (get 2 abr4 = Some "d");
  assert (get 3 abr4 = Some "c");

  (* Test de la fonction extract_min *)
  let abr5 = N (2, "a", V, V) in
  assert (extract_min abr5 = ((2, "a"), V));

  let abr6 = N (2, "a", N (1, "b", V, V), N (3, "c", V, V)) in
  assert (extract_min abr6 = ((1, "b"), V));

  (* Test de la fonction del *)
  let abr7 = del 2 abr6 in
  assert (get 2 abr7 = None);
  assert (get 1 abr7 = Some "b");
  assert (get 3 abr7 = Some "c");

  (* Test de la fonction ajouter *)
  let abr8 = ajouter abr7 2 "d" in
  assert (get 2 abr8 = Some "d");
  assert (get 1 abr8 = Some "b");
  assert (get 3 abr8 = Some "c");

  (* Test de la fonction genere_a *)
  assert (genere_a 0 = V);
  assert (genere_a 1 = N (1, (), V, V));
  assert (genere_a 2 = N (1, (), V, N (2, (), V, V)));
  assert (genere_a 3 = N (1, (), V, N (2, (), V, N (3, (), V, V))))
;;
