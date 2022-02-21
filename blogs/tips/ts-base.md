---
title: ts 基础使用
date: 2022-02-20
tags:
 - ts
categories:
 - 小识书屋
---


## 安装 & 编译


- 安装
  ```shell
  cnpm i typescript -g //全局安装ts
  cnpm i -g ts-node //全局安装ts-node
  ```
- 生成 tsconfig.js 配置
  ```shell
  tsc --init
  ```
- 编译
  ```shell
  tsc index.ts
  ```


## TS 类型

```ts
// Boolean 布尔
const flag: boolean = true;


// Number 
const flag: number = 1;


// String 
const flag: string = "hello";


// Enum 枚举
// 普通枚举 初始值默认为 0 其余的成员会会按顺序自动增长 可以理解为数组下标
enum Color {
  RED,
  PINK,
  BLUE,
}

const pink: Color = Color.PINK;
console.log(pink); // 1

// 设置初始值
enum Color {
  RED = 10,
  PINK,
  BLUE,
}
const pink: Color = Color.PINK;
console.log(pink); // 11

// 字符串枚举 每个都需要声明
enum Color {
  RED = "红色",
  PINK = "粉色",
  BLUE = "蓝色",
}

const pink: Color = Color.PINK;
console.log(pink); // 粉色

// 常量枚举 它是使用 const 关键字修饰的枚举，常量枚举与普通枚举的区别是，整个枚举会在编译阶段被删除
const enum Color {
  RED,
  PINK,
  BLUE,
}

const color: Color[] = [Color.RED, Color.PINK, Color.BLUE];
//编译之后的js如下：
var color = [0 /* RED */, 1 /* PINK */, 2 /* BLUE */];
// 可以看到我们的枚举并没有被编译成js代码 只是把color这个数组变量编译出来了


// array
const flag1: number[] = [1, 2, 3];
const flag2: Array<number> = [1, 2, 3];


// tuple 元组
const flag: [string, number] = ["hello", 1];


// Symbol
// 我们在使用 Symbol 的时候，必须添加 es6 的编译辅助库 需要在 tsconfig.json 的 libs 字段加上ES2015 Symbol 的值是唯一不变的
const sym1 = Symbol("hello");

// any
const flag: any = document.getElementById("root");


// null 和 undefined
let u: undefined = undefined;
let n: null = null;


// Unknown
// unknown类型只能被赋值给 any 类型和 unknown 类型本身
let value: unknown;

value = true; // OK
value = 42; // OK
value = "Hello World"; // OK
value = []; // OK
value = {}; // OK

let value1: unknown = value; // OK
let value2: any = value; // OK
let value3: boolean = value; // Error
let value4: number = value; // Error
let value5: string = value; // Error
let value6: object = value; // Error


// void
function hello(name: string): void {}


// never 
// never 一般表示用户无法达到的类型 例如never 类型是那些总是会抛出异常或根本就不会有返回值的函数表达式或箭头函数表达式的返回值类型
function neverReach(): never {
  throw new Error("an error");
}


// BigInt 
// 使用 BigInt 可以安全地存储和操作大整数 我们在使用 BigInt 的时候 必须添加 ESNext 的编译辅助库 需要在 tsconfig.json 的 libs 字段加上ESNext 要使用1n需要 "target": "ESNext" number 和 BigInt 类型不一样 不兼容
const max1 = Number.MAX_SAFE_INTEGER; // 2**53-1
console.log(max1 + 1 === max1 + 2); //true

const max2 = BigInt(Number.MAX_SAFE_INTEGER);
console.log(max2 + 1n === max2 + 2n); //false

let foo: number;
let bar: bigint;
foo = bar; //error
bar = foo; //error


// object, Object 和 {} 类型
// object 类型用于表示非原始类型
let objectCase: object;
objectCase = 1; // error
objectCase = "a"; // error
objectCase = true; // error
objectCase = null; // error
objectCase = undefined; // error
objectCase = {}; // ok

// 大 Object 代表所有拥有 toString、hasOwnProperty 方法的类型 所以所有原始类型、非原始类型都可以赋给 Object(严格模式下 null 和 undefined 不可以)
let ObjectCase: Object;
ObjectCase = 1; // ok
ObjectCase = "a"; // ok
ObjectCase = true; // ok
ObjectCase = null; // error
ObjectCase = undefined; // error
ObjectCase = {}; // ok

// {} 空对象类型和大 Object 一样 也是表示原始类型和非原始类型的集合
```

### 类型推论
指编程语言中能够自动推导出值的类型的能力


### 联合类型

```ts
let name: string | number;
console.log(name.toString());
name = 1;
console.log(name.toFixed(2));
name = "hello";
console.log(name.length);
```

### 类型断言
```ts
// 尖括号 语法
let someValue: any = "this is a string";
let strLength: number = (<string>someValue).length;

// as 语法
let someValue: any = "this is a string";
let strLength: number = (someValue as string).length;

// 非空断言
let flag: null | undefined | string;
flag!.toString(); // ok
flag.toString(); // error
```

### 字面量类型


### 类型别名
```ts
type flag = string | number;

function hello(value: flag) {}
```


### 交叉类型
```ts
type Flag1 = { x: number };
type Flag2 = Flag1 & { y: string };

let flag3: Flag2 = {
  x: 1,
  y: "hello",
  henb,
};
```


### 类型保护

**typeof 类型保护**

```ts
function double(input: string | number | boolean) {
  if (typeof input === "string") {
    return input + input;
  } else {
    if (typeof input === "number") {
      return input * 2;
    } else {
      return !input;
    }
  }
}
```


**in 关键字**

```ts
interface Bird {
  fly: number;
}

interface Dog {
  leg: number;
}

function getNumber(value: Bird | Dog) {
  if ("fly" in value) {
    return value.fly;
  }
  return value.leg;
}
```


**instanceof 类型保护**

```ts
class Animal {
  name!: string;
}
class Bird extends Animal {
  fly!: number;
}
function getName(animal: Animal) {
  if (animal instanceof Bird) {
    console.log(animal.fly);
  } else {
    console.log(animal.name);
  }
}
```


**自定义类型保护**

通过 type is xxx这样的类型谓词来进行类型保护

例如下面的例子 value is object就会认为如果函数返回 true 那么定义的 value 就是 object 类型


```ts
function isObject(value: unknown): value is object {
  return typeof value === "object" && value !== null;
}

function fn(x: string | object) {
  if (isObject(x)) {
    // ....
  } else {
    // .....
  }
}
```

## 函数


### 函数的定义

```ts
function hello(name: string): void {
  console.log("hello", name);
}
hello("hahaha");
```


### 函数表达式

```ts
type SumFunc = (x: number, y: number) => number;

let countNumber: SumFunc = function (a, b) {
  return a + b;
};
```


### 可选参数

在 TS 中函数的形参和实参必须一样，不一样就要配置可选参数,而且必须是最后一个参数

```ts
function print(name: string, age?: number): void {
  console.log(name, age);
}
print("hahaha");
```


### 默认参数

```ts
function ajax(url: string, method: string = "GET") {
  console.log(url, method);
}
ajax("/users");
```


### 剩余参数

```ts
function sum(...numbers: number[]) {
  return numbers.reduce((val, item) => (val += item), 0);
}
console.log(sum(1, 2, 3));
```


### 函数重载

```ts
let obj: any = {};
function attr(val: string): void;
function attr(val: number): void;
function attr(val: any): void {
  if (typeof val === "string") {
    obj.name = val;
  } else {
    obj.age = val;
  }
}
attr("hahaha");
attr(9);
attr(true);
console.log(obj);
```



## 类


### 类的定义

```ts
class Person {
  name!: string; //如果初始属性没赋值就需要加上!
  constructor(_name: string) {
    this.name = _name;
  }
  getName(): void {
    console.log(this.name);
  }
}
let p1 = new Person("hello");
p1.getName();


class Person {
  constructor(public name: string) {}
  getName(): void {
    console.log(this.name);
  }
}
let p1 = new Person("hello");
p1.getName();
```


### 存取器

```ts
class User {
  myname: string;
  constructor(myname: string) {
    this.myname = myname;
  }
  get name() {
    return this.myname;
  }
  set name(value) {
    this.myname = value;
  }
}

let user = new User("hello");
user.name = "world";
console.log(user.name);
```


### readonly 只读属性

```ts
class Animal {
  public readonly name: string;
  constructor(name: string) {
    this.name = name;
  }
  changeName(name: string) {
    this.name = name; //这个ts是报错的
  }
}

let a = new Animal("hello");
```


### 继承

```ts
class Person {
  name: string; //定义实例的属性，默认省略public修饰符
  age: number;
  constructor(name: string, age: number) {
    //构造函数
    this.name = name;
    this.age = age;
  }
  getName(): string {
    return this.name;
  }
  setName(name: string): void {
    this.name = name;
  }
}

class Student extends Person {
  no: number;
  constructor(name: string, age: number, no: number) {
    super(name, age);
    this.no = no;
  }
  getNo(): number {
    return this.no;
  }
}
let s1 = new Student("hello", 10, 1);
console.log(s1);
```


### 类里面的修饰符

```ts
class Parent {
  public name: string; // 其它任何地方外边都可以访问
  protected age: number; // 子类 都可以访问,其它任何地方不能访问
  private car: number; // 类里面可以访问，子类和其它任何地方都不可以访问
  constructor(name: string, age: number, car: number) {
    //构造函数
    this.name = name;
    this.age = age;
    this.car = car;
  }
  getName(): string {
    return this.name;
  }
  setName(name: string): void {
    this.name = name;
  }
}

class Child extends Parent {
  constructor(name: string, age: number, car: number) {
    super(name, age, car);
  }
  desc() {
    console.log(`${this.name} ${this.age} ${this.car}`); //car访问不到 会报错
  }
}

let child = new Child("hello", 10, 1000);
console.log(child.name);
console.log(child.age); //age访问不到 会报错
console.log(child.car); //car访问不到 会报错
```


### 静态属性 静态方法

类的静态属性和方法是直接定义在类本身上面的 所以也只能通过直接调用类的方法和属性来访问

```ts
class Parent {
  static mainName = "Parent";
  static getmainName() {
    console.log(this); //注意静态方法里面的this指向的是类本身 而不是类的实例对象 所以静态方法里面只能访问类的静态属性和方法
    return this.mainName;
  }
  public name: string;
  constructor(name: string) {
    //构造函数
    this.name = name;
  }
}
console.log(Parent.mainName);
console.log(Parent.getmainName());
```


### 抽象类和抽象方法

抽象类，无法被实例化，只能被继承并且无法创建抽象类的实例 子类可以对抽象类进行不同的实现

抽象方法只能出现在抽象类中并且抽象方法不能在抽象类中被具体实现，只能在抽象类的子类中实现（必须要实现）

使用场景： 我们一般用抽象类和抽象方法抽离出事物的共性 以后所有继承的子类必须按照规范去实现自己的具体逻辑 这样可以增加代码的可维护性和复用性


```ts
abstract class Animal {
  name!: string;
  abstract speak(): void;
}
class Cat extends Animal {
  speak() {
    console.log("喵喵喵");
  }
}
let animal = new Animal(); //直接报错 无法创建抽象类的实例
let cat = new Cat();
cat.speak();
```


## 接口

接口既可以在面向对象编程中表示为行为的抽象，也可以用来描述对象的形状

### 对象的形状

```ts
//接口可以用来描述`对象的形状`
//接口可以用来描述`对象的形状`
interface Speakable {
  speak(): void;
  readonly lng: string; //readonly表示只读属性 后续不可以更改
  name?: string; //？表示可选属性
}

let speakman: Speakable = {
  //   speak() {}, //少属性会报错
  name: "hello",
  lng: "en",
  age: 111, //多属性也会报错
};
```


### 行为的抽象

```ts
//接口可以在面向对象编程中表示为行为的抽象
interface Speakable {
  speak(): void;
}
interface Eatable {
  eat(): void;
}
//一个类可以实现多个接口
class Person implements Speakable, Eatable {
  speak() {
    console.log("Person说话");
  }
  //   eat() {} //需要实现的接口包含eat方法 不实现会报错
}
```


### 定义任意属性

```ts
interface Person {
  id: number;
  name: string;
  [propName: string]: any;
}

let p1 = {
  id: 1,
  name: "hello",
  age: 10,
};
```


### 接口的继承

```ts
interface Speakable {
  speak(): void;
}
interface SpeakChinese extends Speakable {
  speakChinese(): void;
}
class Person implements SpeakChinese {
  speak() {
    console.log("Person");
  }
  speakChinese() {
    console.log("speakChinese");
  }
}
```


### 函数类型接口

```ts
interface discount {
  (price: number): number;
}
let cost: discount = function (price: number): number {
  return price * 0.8;
};
```


### 构造函数的类型接口

```ts
class Animal {
  constructor(public name: string) {}
}
//不加new是修饰函数的,加new是修饰类的
interface WithNameClass {
  new (name: string): Animal;
}
function createAnimal(clazz: WithNameClass, name: string) {
  return new clazz(name);
}
let a = createAnimal(Animal, "hello");
console.log(a.name);
```


> 接口和类型别名的区别

1. 基础数据类型 与接口不同
    ```ts
    // primitive
    type Name = string;

    // union
    type PartialPoint = PartialPointX | PartialPointY;

    // tuple
    type Data = [number, string];

    // dom
    let div = document.createElement("div");
    type B = typeof div;
    ```
2. 重复定义
   ```ts
    interface Point {
        x: number;
    }
    interface Point {
        y: number;
    }
    const point: Point = { x: 1, y: 2 };
   ```
3. 扩展 接口可以扩展类型别名，同理，类型别名也可以扩展接口。
   ```ts
   // 接口扩展接口
    interface PointX {
        x: number;
    }

    interface Point extends PointX {
        y: number;
    }
    // ----
    // 类型别名扩展类型别名
    type PointX = {
        x: number;
    };

    type Point = PointX & {
        y: number;
    };
    // ----
    // 接口扩展类型别名
    type PointX = {
        x: number;
    };
    interface Point extends PointX {
        y: number;
    }
    // ----
    // 类型别名扩展接口
    interface PointX {
        x: number;
    }
    type Point = PointX & {
        y: number;
    };
    ```
4. 实现 这里有一个特殊情况 类无法实现定义了联合类型的类型别名
    ```ts
    type PartialPoint = { x: number } | { y: number };

    // A class can only implement an object type or
    // intersection of object types with statically known members.
    class SomePartialPoint implements PartialPoint {
        // Error
        x = 1;
        y = 2;
    }
    ```


## 泛型


泛型（Generics）是指在定义函数、接口或类的时候，不预先指定具体的类型，而在使用的时候再指定类型的一种特性

```ts
function createArray(length: number, value: any): any[] {
  let result = [];
  for (let i = 0; i < length; i++) {
    result[i] = value;
  }
  return result;
}

createArray(3, "x"); // ['x', 'x', 'x']
```


使用泛型改造

```ts
function createArray<T>(length: number, value: T): Array<T> {
  let result: T[] = [];
  for (let i = 0; i < length; i++) {
    result[i] = value;
  }
  return result;
}

createArray<string>(3, "x"); // ['x', 'x', 'x']
```


### 多个类型参数

```ts
function swap<T, U>(tuple: [T, U]): [U, T] {
  return [tuple[1], tuple[0]];
}

swap([7, "seven"]); // ['seven', 7]
```


### 泛型约束


```ts
function loggingIdentity<T>(arg: T): T {
  console.log(arg.length);
  return arg;
}

// index.ts(2,19): error TS2339: Property 'length' does not exist on type 'T'.
```
上例中，泛型 T 不一定包含属性 length，所以编译的时候报错了。


这时，我们可以对泛型进行约束，只允许这个函数传入那些包含 length 属性的变量。这就是泛型约束

```ts
interface Lengthwise {
  length: number;
}

function loggingIdentity<T extends Lengthwise>(arg: T): T {
  console.log(arg.length);
  return arg;
}
```

> 注意：我们在泛型里面使用extends关键字代表的是泛型约束 需要和类的继承区分开


### 泛型接口

```ts
interface Cart<T> {
  list: T[];
}
let cart: Cart<{ name: string; price: number }> = {
  list: [{ name: "hello", price: 10 }],
};
console.log(cart.list[0].name, cart.list[0].price);
```


### 泛型类

```ts
class MyArray<T> {
  private list: T[] = [];
  add(value: T) {
    this.list.push(value);
  }
  getMax(): T {
    let result = this.list[0];
    for (let i = 0; i < this.list.length; i++) {
      if (this.list[i] > result) {
        result = this.list[i];
      }
    }
    return result;
  }
}
let arr = new MyArray();
arr.add(1);
arr.add(2);
arr.add(3);
let ret = arr.getMax();
console.log(ret);
```


### 泛型类型别名


```ts
type Cart<T> = { list: T[] } | T[];
let c1: Cart<string> = { list: ["1"] };
let c2: Cart<number> = [1];
```



### 泛型参数的默认类型

```ts
function createArray<T = string>(length: number, value: T): Array<T> {
  let result: T[] = [];
  for (let i = 0; i < length; i++) {
    result[i] = value;
  }
  return result;
}
```


## 实用技巧


### typeof 关键词

```ts
//先定义变量，再定义类型
let p1 = {
  name: "hello",
  age: 10,
  gender: "male",
};
type People = typeof p1;
function getName(p: People): string {
  return p.name;
}
getName(p1);
```


### keyof 关键词

```ts
interface Person {
  name: string;
  age: number;
  gender: "male" | "female";
}
//type PersonKey = 'name'|'age'|'gender';
type PersonKey = keyof Person;

function getValueByKey(p: Person, key: PersonKey) {
  return p[key];
}
let val = getValueByKey({ name: "hello", age: 10, gender: "male" }, "name");
console.log(val);
```


### 索引访问操作符

```ts
interface Person {
  name: string;
  age: number;
}

type x = Person["name"]; // x is string
```









