(* Renvoie true ssi les deux reines de coordonnees
   (i, j) et (x, y) ne se menacent mutuellement *)
let visible i j x y : bool = i = x || j = y || x - i = y - j || x - i = j - y

let rec valid_queen (queens : (int * int) list) (i : int) (j : int) : bool =
  match queens with
  | [] -> true
  | [ (x, y) ] -> not (visible i j x y)
  | (x, y) :: t -> (not (visible i j x y)) && valid_queen t i j
;;

(* Renvoie la liste des coordonnées des cases de la ligne i qui ne sont pas menacées *)
let all_valid_queens (n : int) (queens : (int * int) list) (i : int) :
    (int * int) list =
  let rec iter n queens i j acc =
    if j > n then acc
    else if valid_queen queens i j then iter n queens i (j + 1) ((i, j) :: acc)
    else iter n queens i (j + 1) acc
  in
  iter n queens i 1 []
;;

(* Renvoie None <=> pas de solution. Sinon renvoie la solution sous la forme Some [(x1, y1); (x2, y2); ...] *)
let rec aux n queens acc i : (int * int) list option =
  match acc with
  | [] -> None
  | (x, y) :: t ->
      let suiv = n_queens n ((x, y) :: queens) i in
      if suiv = None then aux n queens t i else suiv

and n_queens (n : int) (queens : (int * int) list) (i : int) :
    (int * int) list option =
  if i >= n then Some queens
  else aux n queens (all_valid_queens n queens (i + 1)) (i + 1)
;;

let test () : unit =
  assert (visible 8 2 6 4);
  assert (valid_queen [ (4, 2); (5, 3); (5, 5); (7, 5); (7, 3); (8, 2) ] 3 4);

  assert (n_queens 3 [] 0 = None);
  assert (n_queens 8 [] 0 != None)
;;

test ()

(* Solution pour n = 24 :
     Some
      [(24, 10); (23, 8); (22, 18); (21, 12); (20, 9); (19, 13); (18, 17);
        (17, 19); (16, 4); (15, 15); (14, 1); (13, 5); (12, 2); (11, 6); (10, 3);
        (9, 7); (8, 11); (7, 14); (6, 16); (5, 21); (4, 23); (3, 20); (2, 22);
        (1, 24)]

    Solution pour n = 30 (a tourné pendant 10 minutes...):
    Some
      [(30, 12); (29, 10); (28, 17); (27, 14); (26, 11); (25, 13); (24, 25);
        (23, 23); (22, 21); (21, 19); (20, 15); (19, 2); (18, 4); (17, 1);
        (16, 7); (15, 9); (14, 6); (13, 3); (12, 5); (11, 8); (10, 24); (9, 16);
        (8, 18); (7, 20); (6, 22); (5, 27); (4, 29); (3, 26); (2, 28); (1, 30)]
*)

(* Pouvait-on optimiser mon algo ? Ou est-ce normal qu'il ait mis 10mn à trouver la solution ?
   Limites du backtracking, peut-être... *)
