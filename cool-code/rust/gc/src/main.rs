fn main() {
    let s = "hello";
    let ss = {
        let ss = "world";
        //ss += "assSA地自己那关西北处".to_string();
        ss
    };
    println!("{},{}!",s,ss);
    
    let mut s = String::from("hello");
    s.push_str(",world!");
    println!("push_str is {}",s);
    let x = 5;
    let y = x;
    let s1 = String::from("hello");
    let s2 = s1;
    let s3 = s2.clone();
    let ss = "sadads";
    let ss1 = ss;
    println!("x{} , y{},ss{},ss1{},",x,y,ss,ss1);
    println!("{}{}{} ,world!1!!!",y,s2,s3);
}
