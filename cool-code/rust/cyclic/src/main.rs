fn main() {
    println!("Hello, world!");
    let mut counter = 0;

    let result = loop {
        counter += 1;

        if counter == 10 {
            break counter * 2;

        }

    };

    println!("The result is {}", result);
    let mut number = 3;
    while number != 0 {
        println!("{}!",number);
        number = number - 1;
    }
    println!("LIFTOFF!!!ZQ");
    
    let a  = [2134,2,4345,3455435,32354,5,43525];
    let mut index = 0;
    while index < 5 {
        println!("the value is : {}",a[index]);
        index += 1;
    }
    println!("for cyclic");

    for element in a.iter() {
        println!("the value is : {}",element);
    }
    for number in (1..4)/*.rev()*/ {
        println!("{}!",a[number]);
    }
    println!("LIIIFFO!!ZZ!");
}
