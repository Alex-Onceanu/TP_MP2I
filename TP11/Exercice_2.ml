(* 'k est le type des clés, 'v celui des valeurs *)
type ('k, 'v) abr = V | N of 'k * 'v * ('k, 'v) abr * ('k, 'v) abr

let rec get (key : 'k) (a : ('k, 'v) abr) : 'v option =
  match a with
  | V -> None
  | N (c, v, g, d) ->
      if key = c then Some v else if key < c then get key g else get key d
;;

let rec set (key : 'k) (value : 'v) (a : ('k, 'v) abr) : ('k, 'v) abr =
  match a with
  | V -> V
  | N (c, v, g, d) ->
      if key = c then N (c, value, g, d)
      else if key < c then N (c, v, set key value g, d)
      else N (c, v, g, set key value d)
;;

let rec extract_min (a : ('k, 'v) abr) : ('k * 'v) * ('k, 'v) abr =
  match a with
  | V -> failwith "Extraction sur feuille impossible"
  | N (c, v, V, d) -> ((c, v), V)
  | N (c, v, g, d) -> extract_min g
;;

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

let rec ajouter (a : ('k, 'v) abr) (key : 'k) (value : 'v) : ('k, 'v) abr =
  match a with
  | V -> N (key, value, V, V)
  | N (c, v, g, d) ->
      if key < c then N (c, v, ajouter g key value, d)
      else if key > c then N (c, v, g, ajouter d key value)
      else failwith "doublon de clé !"
;;

let rec genere_a (n : int) : (int, unit) abr =
  if n = 0 then V else ajouter (genere_a (n - 1)) n ()
;;

let time_abr (n : int) : float =
  let debut = Sys.time () in
  let _ = genere_a n in
  Sys.time () -. debut
;;

let rec tableau_time_abr (n_min : int) (n_max : int) (pas : int) : float list =
  if n_min > n_max then []
  else time_abr n_min :: tableau_time_abr (n_min + pas) n_max pas
;;
