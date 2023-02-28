type boisson =
| Eau
| Jus of string (* nom du fruit *)
| Cola of bool (* true = light, false = normal *)
| Cocktail of float * boisson * boisson

let rec prix (b : boisson) : (float)=
  match b with
  | Eau -> 0.0
  | Jus s -> if s = "ramboutan" then 5.3 else 3.0
  | Cola s -> 1.0
  | Cocktail(p, x, y) -> (p *. prix x) +. (1.0 -. p) *. prix y
;;

let rec shaker (l : boisson list) =
  match l with
  | [] -> failwith "Le verre est vide."
  | x::[] -> x
  | h::t -> Cocktail(0.5, h, shaker t)
;;

let string_of_boisson (b : boisson) =
  match b with
  | Eau -> "Eau"
  | Jus s -> "Jus de " ^ s
  | Cola x -> if x then "Breizh Cola light" else "Breizh Cola"
  | Cocktail _ -> failwith "Les cocktails ne sont atomiques."
;;

let ingredients (b : boisson) : (boisson * float) list =
  let rec ingr_avec_proportion b (prop : float) =
    match b with
    | Eau | Jus _ | Cola _ -> (b, prop)::[]
    | Cocktail(p, g, d) -> (ingr_avec_proportion g (prop *. p)) @ (ingr_avec_proportion d (prop *. (1. -. p))) 
  in ingr_avec_proportion b 1.
;;



let rec ajoute (b : (boisson * float)) (l : (boisson * float) list) =
  match l with
  | [] -> [b]
  | h::t -> let g1, d1 = b in let g2, d2 = h 
    in if g1 = g2 then (g1, d1 +. d2)::t else h::(ajoute b t)
;;

let dedoublonner (l : (boisson * float) list) : (boisson * float) list =
  let rec cumule_doublons l (acc : (boisson * float) list) =
    match l with
    | [] -> acc
    | h::t -> cumule_doublons t (ajoute h acc)
  in cumule_doublons l []
;;

let recette (b : boisson) : unit =
  print_string "Recette pour 1L:\n";
  let rec affiche_ingredients (l : (boisson * float) list) : unit =
    match l with
    | [] -> ()
    | h::t -> let ty, qt = h in
      let _ = print_string (string_of_int (int_of_float(qt *. 1000.)) ^ " mL " ^ string_of_boisson ty ^ "\n") in
      affiche_ingredients t

  in affiche_ingredients (dedoublonner (ingredients b))
;;


let test() =
  (* breizh coca light à moitié dilué : pas très appetissant mais au moins c'est pas cher. *)
  assert(prix (Cocktail (0.5, Cola(true), Eau)) = 0.5);

  assert(ingredients (shaker [Jus "Orange"; Eau; Cola true; Eau])
    = [(Jus "Orange", 0.5); (Eau, 0.25); (Cola true, 0.125); (Eau, 0.125)]);

  assert (dedoublonner (ingredients (shaker [Jus "Orange"; Eau; Cola true; Eau]))
    = [(Jus "Orange", 0.5); (Eau, 0.375); (Cola true, 0.125)]);
    
  recette (Cocktail(0.05, Eau, Cocktail(0.4211, Jus "Raisin", Cocktail(0.545, Cola false, Jus "Orange"))));

  print_string "Tous les tests ont reussi.\n";
;;

test();;


(* Je ferai le bonus sur le tri rapide de mon coté, j'ai beaucoup de travail pour le moment je dois rendre le TP. *)
(* Surtout que le tri rapide est super intéressant.. *)