fn main() {
    println!("Hello, world!");
    let mut x:u32 = 5;
    println!("value x = {}",x);
    x = 234;
    println!("value x = {}",x);
    
    const MAX_POINTS:u32 = 100_000;
    println!("const value max_point = {}",MAX_POINTS);
    x = MAX_POINTS;
    println!("value x = {}",x);


    let xx = 233;
    println!("value xx= {}",xx);
    let xx = xx + 212;
    println!("value xx= {}",xx);
    let xx = xx * 212;
    println!("value xx= {}",xx);
    let space = "       ";
    println!("space length = {}",space.len());
    let mut space = "       ";
    println!("space length = {}",space.len());
    space = " 递归哦      ";
    println!("space length = {}",space.len());

    let guess:u32 = "42".parse().expect("Not a number!");
    println!("guess value = {}",guess);
    let v = 2134_2345u32;
    println!("guess value = {}",v);
    let x = 2.0;
    let y:f32 = 2.0;
    println!("x = {},y = {}",x,y);
    let c = 'z';
    let z = 'ℤ';
    let heart_eyed_cat = '😻';
    println!("c = [{}],z = [{}],heart_eyed_cat = [({})]",c,z,heart_eyed_cat);
    let mut tup:(i32,f64,u32) = (200_333,6.344,12);//.expcet("Tuple");
    let (x,y,z) = tup;
    println!("tuple tup = {}    {}    {}",x,y,z);
    tup = (3122,43.23,232);
    println!("tuple tup = {}    {}    {}",tup.0,tup.1,tup.2);
    let arr = [1,2,3,4,5];
    println!("arr value {}",arr[0]);

    //#![allow(unused)]
    let months = ["January", "February", "March", "April", "May", "June", "July",
                      "August", "September", "October", "November", "December"];
    println!("output months = {}",months[0]);
    let arr:[u64;3] = [546,654,3645];
    println!("arr value {}",arr[0]);
    let arr = [3;4] ;
    println!("arr value {}",arr[0]);


}
