(* Renvoie a / b ou None si b = 0 *)
let division_opt (a : int) (b : int) : int option =
  if b = 0 then None else Some (a / b)
;;

let rec max_opt (l : 'a list) : 'a option =
  match l with
  | [] -> None
  | x :: q -> (
      match max_opt q with
      | None -> Some x
      | Some j -> Some (max x j))
;;

(* Renvoie f o ou None si o est None *)
let option_map (f : 'a -> 'b) (o : 'a option) : 'b option =
  match o with
  | None -> None
  | Some x -> Some (f x)
;;

(* Renvoie a + b ou None si (a est None ou b est None) *)
let add_opt (a : int option) (b : int option) : int option =
  match (a, b) with
  | Some xa, Some xb -> Some (xa + xb)
  | _ -> None
;;

(* Renvoie f a b ou None si (a est None ou b est None) *)
let binop_opt (f : 'a -> 'a -> 'a) (a : 'a option) (b : 'a option) : 'a option =
  match (a, b) with
  | Some xa, Some xb -> Some (f xa xb)
  | _ -> None
;;

exception VariableIntrouvable of string

type context = (string * int) list

type arith_expr =
  | Int of int
  | Var of string
  | Plus of arith_expr * arith_expr
  | Fois of arith_expr * arith_expr

(* __________________________expr.ml avec exceptions___________________________ *)

(* Renvoie la valeur associée à une certaine variable x du contexte *)
let rec get_var (x : string) (c : context) : int =
  match c with
  | [] -> raise (VariableIntrouvable x)
  | (y, n) :: q -> if x = y then n else get_var x q
;;

(* Evalue une expression arithmétique et renvoie le résultat *)
let rec eval (e : arith_expr) (c : context) : int =
  match e with
  | Int n -> n
  | Var v -> get_var v c
  | Plus (e1, e2) -> eval e1 c + eval e2 c
  | Fois (e1, e2) -> eval e1 c * eval e2 c
;;

(* __________________________expr.ml avec options___________________________________ *)

(* Renvoie la valeur associée à une certaine variable x du contexte *)
let rec get_var_opt (x : string) (c : context) : int option =
  match c with
  | [] -> None
  | (y, n) :: q -> if x = y then Some n else get_var_opt x q
;;

(* Evalue une expression arithmétique et renvoie le résultat *)
let rec eval_opt (e : arith_expr) (c : context) : int option =
  match e with
  | Int n -> Some n
  | Var v -> get_var_opt v c
  | Plus (e1, e2) -> binop_opt ( + ) (eval_opt e1 c) (eval_opt e2 c)
  | Fois (e1, e2) -> binop_opt ( * ) (eval_opt e1 c) (eval_opt e2 c)
;;

let test () =
  (* tests ici *)
  assert (
    eval_opt (Fois (Plus (Int 3, Int 4), Fois (Int 3, Int 2))) []
    = Some ((3 + 4) * (3 * 2)));
  assert (eval_opt (Plus (Int 5, Var "X")) [ ("X", 4) ] = Some 9);
  assert (eval_opt (Plus (Int 5, Var "bottom")) [ ("X", 4) ] = None);

  let res =
    try eval (Plus (Int 5, Var "bottom")) [ ("X", 4) ]
    with VariableIntrouvable x -> 0
  in
  assert (res = 0)
;;

test ()
