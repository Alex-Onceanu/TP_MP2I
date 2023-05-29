let f n =
  match n with
  | 1 -> 1
  | 2 -> 2
  | 3 -> 4
  | 4 -> 1
  | 5 -> 7
  | 6 -> 9
  | 7 -> 11
  | 8 -> 10
  | _ -> 0
;;

(* Renvoie 0 en cas de liste vide, sinon le plus grand élément de l *)
let rec maximum (l : int list) : int =
  match l with
  | [] -> 0
  | h :: t -> max h (maximum t)
;;

(* Renvoie le couple du plus grand element de la liste avec son indice dans la liste *)
let maximum_couple l =
  let rec aux l i =
    match l with
    | [] -> failwith "Liste vide"
    | x :: [] -> (i, x)
    | h :: t ->
        (fun (a, b) (c, d) -> if b > d then (a, b) else (c, d))
          (i, h)
          (aux t (i + 1))
  in
  aux l 0
;;

(* Renvoie { 1, 2, ..., n } *)
let rec range n =
  match n with
  | 0 -> []
  | _ -> n :: range (n - 1)
;;

(* Pas opti pour n = 3 et [5; 5; 6]*)
let rec glouton_prix (f : int -> int) (n : int) : int =
  if n <= 0 then 0
  else
    let x, p =
      maximum_couple
        (List.map (fun x -> if x <= n then f x else 0) (List.rev (range n)))
    in
    if p = 0 then 0 else p + glouton_prix f (n - x - 1)
;;

let rec glouton_ratio (f : int -> int) (n : int) : int =
  if n <= 0 then 0
  else
    let x, p =
      maximum_couple
        (List.map
           (fun x ->
             if x <= n then Int.to_float (f x) /. Int.to_float x else 0.)
           (List.rev (range n)))
    in
    if p = 0. then 0 else f (x + 1) + glouton_prix f (n - x - 1)
;;

(* C(n) = max { C(n - j) + f(j) | 1 <= j <= n} *)
(* Complexité : O(2^n), pas utilisable a partir de n = 30... *)
let rec decoupe_optimale (f : int -> int) (n : int) : int =
  if n <= 0 then 0
  else maximum (List.map (fun j -> decoupe_optimale f (n - j) + f j) (range n))
;;

(** Valeur optimale pour d ́ecouper une barre de longueur n, selon la fonction de prix f. *)
let decoupe_prog_dyn (f : int -> int) (n : int) =
  let t = Array.make (n + 1) (-1) in

  let rec calculer_decoupe i : int =
    if t.(i) != -1 then t.(i)
    else (
      t.(i) <-
        maximum (List.map (fun j -> calculer_decoupe (i - j) + f j) (range i));
      t.(i))
  in
  calculer_decoupe n
;;
