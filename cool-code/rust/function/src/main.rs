fn get_some_girl(){
    println!("welcome into secret hold~");
    println!("zhayin is bitchQ");
}
fn sum(x:i64,y:i64)->i64{
    let z = x + y;  
    println!("at function {} + {} = {}",x,y,z);
    z
}
fn exec_hun(x:u64)->u64{
    let mut y:u64  = x + x * 2;
    let count:u64 = 1_000;
    let result = loop {
        y  = y + x * 2;
        if y > count {
            break y * 2;
        }
    };
    result
}
fn main() {
    println!("Hello, world!");
    get_some_girl();
    println!("3 + 3 = {}",sum(2,3));
    let  number = 5;
    if number % 4 == 0{
        println!("number is divisiable by 4");
    }else if number % 3 == 0 {
        println!("number is divisiable by 3");
    }else if number % 2 == 0{
        println!("number is divisiable by 2");
    }else{
        println!("gefsfgwes other value");
    }
    let condition = true;
    let number = if condition {
        5
    }else{
      6//"six"  
    };
    println!("The value of number is : {}",number);
    let mut value:u64 = 0;
    loop{
        value += 1;
        println!("value = {}",value);
        if value == 100{
            break;
        }
    }
    let x = exec_hun(123);
    println!("exec fun result is {}",x);
}
