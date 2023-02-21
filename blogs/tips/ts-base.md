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


### 映射类型 in

```ts
interface Person {
  name: string;
  age: number;
  gender: "male" | "female";
}
//批量把一个接口中的属性都变成可选的
type PartPerson = {
  [Key in keyof Person]?: Person[Key];
};

let p1: PartPerson = {};
```


### infer 关键字

在条件类型语句中，可以用 infer 声明一个类型变量并且对它进行使用

```ts
type ReturnType<T> = T extends (...args: any[]) => infer R ? R : any;
```

以上代码中 infer R 就是声明一个变量来承载传入函数签名的返回值类型，简单说就是用它取到函数返回值的类型方便之后使用。


### 内置工具类型

1. Exclude<T,U> 从 T 可分配给的类型中排除 U
    ```ts
    type Exclude<T, U> = T extends U ? never : T;

    type E = Exclude<string | number, string>;
    let e: E = 10;
    ```
2. Extract<T,U> 从 T 可分配给的类型中提取 U
   ```ts
    type Extract<T, U> = T extends U ? T : never;

    type E = Extract<string | number, string>;
    let e: E = "1";
   ```
3. NonNullable 从 T 中排除 null 和 undefined
   ```ts
    type NonNullable<T> = T extends null | undefined ? never : T;

    type E = NonNullable<string | number | null | undefined>;
    let e: E = null;
   ```
4. ReturnType infer 最早出现在此 PR 中，表示在 extends 条件语句中待推断的类型变量
   ```ts
    type ReturnType<T extends (...args: any[]) => any> = T extends (
        ...args: any[]
    ) => infer R
        ? R
        : any;
    function getUserInfo() {
        return { name: "hello", age: 10 };
    }

    // 通过 ReturnType 将 getUserInfo 的返回值类型赋给了 UserInfo
    type UserInfo = ReturnType<typeof getUserInfo>;

    const userA: UserInfo = {
        name: "hello",
        age: 10,
    };
   ```
5. Parameters 该工具类型主要是获取函数类型的参数类型
   ```ts
    type Parameters<T> = T extends (...args: infer R) => any ? R : any;

    type T0 = Parameters<() => string>; // []
    type T1 = Parameters<(s: string) => void>; // [string]
    type T2 = Parameters<<T>(arg: T) => T>; // [unknown]
   ```
6. Partial Partial 可以将传入的属性由非可选变为可选
   ```ts
    type Partial<T> = { [P in keyof T]?: T[P] };
    interface A {
      a1: string;
      a2: number;
      a3: boolean;
    }
    type aPartial = Partial<A>;
    const a: aPartial = {}; // 不会报错
   ```
7. Required Required 可以将传入的属性中的可选项变为必选项，这里用了 -? 修饰符来实现。
   ```ts
    interface Person {
        name: string;
        age: number;
        gender?: "male" | "female";
    }
    /**
    * type Required<T> = { [P in keyof T]-?: T[P] }; 
    */
    let p: Required<Person> = {
        name: "hello",
        age: 10,
        gender: "male",
    };
   ```
8. Readonly Readonly 通过为传入的属性每一项都加上 readonly 修饰符来实现。
   ```ts
    interface Person {
        name: string;
        age: number;
        gender?: "male" | "female";
    }
    //type Readonly<T> = { readonly [P in keyof T]: T[P] };
    let p: Readonly<Person> = {
        name: "hello",
        age: 10,
        gender: "male",
    };
    p.age = 11; //error
   ```
9.  Pick<T,K> Pick 能够帮助我们从传入的属性中摘取某些返回
    ```ts
    interface Todo {
        title: string;
        description: string;
        done: boolean;
    }
    /**
    * From T pick a set of properties K
    * type Pick<T, K extends keyof T> = { [P in K]: T[P] };
    */
    type TodoBase = Pick<Todo, "title" | "done">;

    // =
    type TodoBase = {
        title: string;
        done: boolean;
    };
    ```
10. Record<K,T> 构造一个类型，该类型具有一组属性 K，每个属性的类型为 T。可用于将一个类型的属性映射为另一个类型。Record 后面的泛型就是对象键和值的类型。
    ```ts
    // type Record<K extends keyof any, T> = {
    // [P in K]: T;
    // };
    type Point = "x" | "y";
    type PointList = Record<Point, { value: number }>;
    const cars: PointList = {
        x: { value: 10 },
        y: { value: 20 },
    };
    ```
11. Omit<K,T> 基于已经声明的类型进行属性剔除获得新类型
    ```ts
    // type Omit=Pick<T,Exclude<keyof T,K>>
    type User = {
        id: string;
        name: string;
        email: string;
    };
    type UserWithoutEmail = Omit<User, "email">;// UserWithoutEmail ={id: string;name: string;}
    ```


## TypeScript 装饰器


### 类装饰器

类装饰器在类声明之前声明，用来监视、修改或替换类定义

```ts
namespace a {
  //当装饰器作为修饰类的时候，会把构造器传递进去
  function addNameEat(constructor: Function) {
    constructor.prototype.name = "hello";
    constructor.prototype.eat = function () {
      console.log("eat");
    };
  }
  @addNameEat
  class Person {
    name!: string;
    eat!: Function;
    constructor() {}
  }
  let p: Person = new Person();
  console.log(p.name);
  p.eat();
}

namespace b {
  //还可以使用装饰器工厂 这样可以传递额外参数
  function addNameEatFactory(name: string) {
    return function (constructor: Function) {
      constructor.prototype.name = name;
      constructor.prototype.eat = function () {
        console.log("eat");
      };
    };
  }
  @addNameEatFactory("hello")
  class Person {
    name!: string;
    eat!: Function;
    constructor() {}
  }
  let p: Person = new Person();
  console.log(p.name);
  p.eat();
}

namespace c {
  //还可以替换类,不过替换的类要与原类结构相同
  function enhancer(constructor: Function) {
    return class {
      name: string = "jiagou";
      eat() {
        console.log("吃饭饭");
      }
    };
  }
  @enhancer
  class Person {
    name!: string;
    eat!: Function;
    constructor() {}
  }
  let p: Person = new Person();
  console.log(p.name);
  p.eat();
}
```


### 属性装饰器

属性装饰器表达式会在运行时当作函数被调用，传入 2 个参数 第一个参数对于静态成员来说是类的构造函数，对于实例成员是类的原型对象 第二个参数是属性的名称

```ts
//修饰实例属性
function upperCase(target: any, propertyKey: string) {
  let value = target[propertyKey];
  const getter = function () {
    return value;
  };
  // 用来替换的setter
  const setter = function (newVal: string) {
    value = newVal.toUpperCase();
  };
  // 替换属性，先删除原先的属性，再重新定义属性
  if (delete target[propertyKey]) {
    Object.defineProperty(target, propertyKey, {
      get: getter,
      set: setter,
      enumerable: true,
      configurable: true,
    });
  }
}

class Person {
  @upperCase
  name!: string;
}

let p: Person = new Person();
p.name = "world";
console.log(p.name);
```


### 方法装饰器

方法装饰器顾名思义，用来装饰类的方法。它接收三个参数：
target: Object - 对于静态成员来说是类的构造函数，对于实例成员是类的原型对象
propertyKey: string | symbol - 方法名
descriptor: TypePropertyDescript - 属性描述符

```ts
//修饰实例方法
function noEnumerable(
  target: any,
  property: string,
  descriptor: PropertyDescriptor
) {
  console.log("target.getName", target.getName);
  console.log("target.getAge", target.getAge);
  descriptor.enumerable = false;
}
//重写方法
function toNumber(
  target: any,
  methodName: string,
  descriptor: PropertyDescriptor
) {
  let oldMethod = descriptor.value;
  descriptor.value = function (...args: any[]) {
    args = args.map((item) => parseFloat(item));
    return oldMethod.apply(this, args);
  };
}

class Person {
  name: string = "hello";
  public static age: number = 10;
  constructor() {}
  @noEnumerable
  getName() {
    console.log(this.name);
  }
  @toNumber
  sum(...args: any[]) {
    return args.reduce((accu: number, item: number) => accu + item, 0);
  }
}

let p: Person = new Person();
for (let attr in p) {
  console.log("attr=", attr);
}

p.getName();

console.log(p.sum("1", "2", "3"));
```


### 参数装饰器

参数装饰器顾名思义，是用来装饰函数参数，它接收三个参数：

target: Object - 被装饰的类 propertyKey: string | symbol - 方法名 parameterIndex: number - 方法中参数的索引值


```ts
function Log(target: Function, key: string, parameterIndex: number) {
  let functionLogged = key || target.prototype.constructor.name;
  console.log(`The parameter in position ${parameterIndex} at ${functionLogged} has
	been decorated`);
}

class Greeter {
  greeting: string;
  constructor(@Log phrase: string) {
    this.greeting = phrase;
  }
}
```


### 装饰器执行顺序

有多个参数装饰器时：从最后一个参数依次向前执行

方法和方法参数中参数装饰器先执行。 方法和属性装饰器，谁在前面谁先执行。因为参数属于方法一部分，所以参数会一直紧紧挨着方法执行


```ts
function Class1Decorator() {
  return function (target: any) {
    console.log("类1装饰器");
  };
}
function Class2Decorator() {
  return function (target: any) {
    console.log("类2装饰器");
  };
}
function MethodDecorator() {
  return function (
    target: any,
    methodName: string,
    descriptor: PropertyDescriptor
  ) {
    console.log("方法装饰器");
  };
}
function Param1Decorator() {
  return function (target: any, methodName: string, paramIndex: number) {
    console.log("参数1装饰器");
  };
}
function Param2Decorator() {
  return function (target: any, methodName: string, paramIndex: number) {
    console.log("参数2装饰器");
  };
}
function PropertyDecorator(name: string) {
  return function (target: any, propertyName: string) {
    console.log(name + "属性装饰器");
  };
}

@Class1Decorator()
@Class2Decorator()
class Person {
  @PropertyDecorator("name")
  name: string = "hello";
  @PropertyDecorator("age")
  age: number = 10;
  @MethodDecorator()
  greet(@Param1Decorator() p1: string, @Param2Decorator() p2: string) {}
}

/**
name属性装饰器
age属性装饰器
参数2装饰器
参数1装饰器
方法装饰器
类2装饰器
类1装饰器
 */
```


## 编译

### tsconfig.json 的作用

- 用于标识 TypeScript 项目的根路径；
- 用于配置 TypeScript 编译器；
- 用于指定编译的文件。

### tsconfig.json 重要字段

- files - 设置要编译的文件的名称；
- include - 设置需要进行编译的文件，支持路径模式匹配；
- exclude - 设置无需进行编译的文件，支持路径模式匹配；
- compilerOptions - 设置与编译流程相关的选项。


### compilerOptions 选项

```ts
{
  "compilerOptions": {

    /* 基本选项 */
    "target": "es5",                       // 指定 ECMAScript 目标版本: 'ES3' (default), 'ES5', 'ES6'/'ES2015', 'ES2016', 'ES2017', or 'ESNEXT'
    "module": "commonjs",                  // 指定使用模块: 'commonjs', 'amd', 'system', 'umd' or 'es2015'
    "lib": [],                             // 指定要包含在编译中的库文件
    "allowJs": true,                       // 允许编译 javascript 文件
    "checkJs": true,                       // 报告 javascript 文件中的错误
    "jsx": "preserve",                     // 指定 jsx 代码的生成: 'preserve', 'react-native', or 'react'
    "declaration": true,                   // 生成相应的 '.d.ts' 文件
    "sourceMap": true,                     // 生成相应的 '.map' 文件
    "outFile": "./",                       // 将输出文件合并为一个文件
    "outDir": "./",                        // 指定输出目录
    "rootDir": "./",                       // 用来控制输出目录结构 --outDir.
    "removeComments": true,                // 删除编译后的所有的注释
    "noEmit": true,                        // 不生成输出文件
    "importHelpers": true,                 // 从 tslib 导入辅助工具函数
    "isolatedModules": true,               // 将每个文件做为单独的模块 （与 'ts.transpileModule' 类似）.

    /* 严格的类型检查选项 */
    "strict": true,                        // 启用所有严格类型检查选项
    "noImplicitAny": true,                 // 在表达式和声明上有隐含的 any类型时报错
    "strictNullChecks": true,              // 启用严格的 null 检查
    "noImplicitThis": true,                // 当 this 表达式值为 any 类型的时候，生成一个错误
    "alwaysStrict": true,                  // 以严格模式检查每个模块，并在每个文件里加入 'use strict'

    /* 额外的检查 */
    "noUnusedLocals": true,                // 有未使用的变量时，抛出错误
    "noUnusedParameters": true,            // 有未使用的参数时，抛出错误
    "noImplicitReturns": true,             // 并不是所有函数里的代码都有返回值时，抛出错误
    "noFallthroughCasesInSwitch": true,    // 报告 switch 语句的 fallthrough 错误。（即，不允许 switch 的 case 语句贯穿）

    /* 模块解析选项 */
    "moduleResolution": "node",            // 选择模块解析策略： 'node' (Node.js) or 'classic' (TypeScript pre-1.6)
    "baseUrl": "./",                       // 用于解析非相对模块名称的基目录
    "paths": {},                           // 模块名到基于 baseUrl 的路径映射的列表
    "rootDirs": [],                        // 根文件夹列表，其组合内容表示项目运行时的结构内容
    "typeRoots": [],                       // 包含类型声明的文件列表
    "types": [],                           // 需要包含的类型声明文件名列表
    "allowSyntheticDefaultImports": true,  // 允许从没有设置默认导出的模块中默认导入。

    /* Source Map Options */
    "sourceRoot": "./",                    // 指定调试器应该找到 TypeScript 文件而不是源文件的位置
    "mapRoot": "./",                       // 指定调试器应该找到映射文件而不是生成文件的位置
    "inlineSourceMap": true,               // 生成单个 soucemaps 文件，而不是将 sourcemaps 生成不同的文件
    "inlineSources": true,                 // 将代码与 sourcemaps 生成到一个文件中，要求同时设置了 --inlineSourceMap 或 --sourceMap 属性

    /* 其他选项 */
    "experimentalDecorators": true,        // 启用装饰器
    "emitDecoratorMetadata": true          // 为装饰器提供元数据的支持
  }
}
```


## 模块和声明文件

### 全局模块



### 文件模块




### 声明文件

typings\jquery.d.ts

```ts
declare const $: (selector: string) => {
  click(): void;
  width(length: number): void;
};
```



### 第三方声明文件

- @types 是一个约定的前缀，所有的第三方声明的类型库都会带有这样的前缀
- JavaScript 中有很多内置对象，它们可以在 TypeScript 中被当做声明好了的类型
- 内置对象是指根据标准在全局作用域（Global）上存在的对象。这里的标准是指 ECMAScript 和其他环境（比如 DOM）的标准
- 这些内置对象的类型声明文件，就包含在 TypeScript 核心库的类型声明文件中,具体可以查看ts 核心声明文件


### 查找声明文件


如果是手动写的声明文件，那么需要满足以下条件之一，才能被正确的识别

- 给 package.json 中的 types 或 typings 字段指定一个类型声明文件地址
- 在项目根目录下，编写一个 index.d.ts 文件
- 针对入口文件（package.json 中的 main 字段指定的入口文件），编写一个同名不同后缀的 .d.ts 文件

```json
{
    "name": "myLib",
    "version": "1.0.0",
    "main": "lib/index.js",
    "types": "myLib.d.ts",
}
```








