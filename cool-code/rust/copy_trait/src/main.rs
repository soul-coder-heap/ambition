fn main() {
    println!("Hello, world!");
    let s = String::from("hello");
    let sp = s.clone();
    tasks_ownership(sp); // move copy
    println!("s string is {}",s);
    let x = 5;
    makes_copy(x);
    let _s1 = gives_ownership();
    let _s2 = String::from("baidu");
    let _s3 = tasks_and_gives_back(_s2);
    let (mut _s4,_len) = calcuate_length(_s3);
    println!("_s3 is {},length is {}",_s4,_len);
    {
        println!("_s4 is {},length is {}",_s4,calcuate_length_reference(&_s4));
        println!("_s4 is {},length is {}",_s4,_s4.len());
    }
    let len = calcuate_length_reference_change(&mut _s4);
    println!("_s4 is {},length is {}",_s4,len);
    println!("_s4 is {},length is {}",_s4,_s4.len());
    
    let mut s = String::from("asdfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaarewqrqwerqwrqwreqwrt532q4652v654ubn567i765nb8i678ib566nii65776i5b465bu4b56b45b45bv45v45v745v7456v7476445645465vb66456666666666666666666666666666666666666666666666666666666666666666666666666666666");
    s.push_str(&_s4);
    s.push_str(&_s4);
    s.push_str(&_s4);
    s.push_str(&_s4);
    println!("s string is {},length is {}",s,s.len());

    let r1 = &s;
    let r2 = &s;

    println!("{}, {}, and ", r1, r2);
    let r3 = &mut s;
    println!("{} ", r3);
    //C
    //C
}
fn tasks_ownership(some_string:String){
    println!("string is {}",some_string);
}
fn makes_copy(some_integer:i32){
    println!("integer is {}",some_integer);
}
fn gives_ownership() -> String {
    let some_string = String::from("hello");
    some_string
}
fn tasks_and_gives_back(a_string:String) -> String {
    a_string
}
fn calcuate_length(s:String) ->  (String,usize){
    let length = s.len();
    (s,length)
}
fn calcuate_length_reference(s:&String) -> usize {
    //s.push_str("i am your farther");
    s.len()
}
fn calcuate_length_reference_change(s:& mut String) -> usize{
    s.push_str("i am your farther");
    s.len()
}
