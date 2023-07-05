(*
Q1) var1 vaut {contents = '3'} et son type est char ref. 
    var2 vaut {contents = 4} et son type est int ref
    On ne peut pas additionner var1 et var2 , ni var2 et 4
*)

let var1 = ref 12;;

(*
Q3) var1 vaut {contents = 12}
    !var1 vaut 3 *)
var1 := 2 * !var1;;
var1 := 10 + !var1

(* var1 vaut {contents = 34}
   !var1 vaut 34 *)
let incrementer : int ref -> unit = fun x -> x := !x + 1

(* Q5) a = {contents = 3}, b = {contents = 6}, c = {contents = 3} *)

let squares1 (n : int) : unit =
  for i = 1 to n do
    print_int (i * i);
    print_string ", "
  done;
  print_string "\n"
;;

let squares2 (n : int) : unit =
  let i = ref 1 in
  while !i <= n do
    print_int (!i * !i);
    i := !i + 1;
    print_string ", "
  done;
  print_string "\n"
;;

let sommes_partielles (t : int array) : int array =
  let n = Array.length t in
  let res = Array.make n 0 in
  let s = ref 0 in
  for i = 0 to n - 1 do
    s := !s + t.(i);
    res.(i) <- !s
  done;
  res
;;

(* blblblblblbl *)
let tri_bulles (t : int array) : unit =
  let n = Array.length t in
  let j = ref (n - 1) in
  while !j > 0 do
    for i = 0 to !j - 1 do
      if t.(i) > t.(i + 1) then begin
        let tmp = t.(i) in
        t.(i) <- t.(i + 1);
        t.(i + 1) <- tmp
      end
    done;
    j := !j - 1
  done
;;

(* NB: ":=" == "walrus operator" *)
(* NB2: for descendant == "for i = n - 1 downto 0 do ... done;" *)
