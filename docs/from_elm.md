## 関数宣言

```elm

plus: Int -> Int -> Int
plus a b = a + b

```


```reasonML

let plus = (a: int, b: int): int => a + b;

```

#### 小洒落た関数


```elm

plus: Int -> Int -> Int
plus a b = 
  let
   aa = a * a
   bb = b * b
  in 
   aa + bb
```

```reasonML

let plus = (a: int, b: int): int => {
  let aa = a * a;
  let bb = b * b;
  aa + bb
};

```



## unionType(的なの)

```elm

type UnionSample = A | B | C Int | D String String

```

```reasonML
type unionSample = A | B | C(int) | D(string, string);
```

## record

```elm
type alias RecordSample = {
  name: String
  , age: Int
  }
```

```reasonML
type recordSample = {
  name: string,
  age: int
}
```

## List
```elm
list = [1,2,3]
```

```reasonML
let list = [1,2,3];
```


## if

```elm
booleanValue: Bool = if number == 1 then true 
else if number == 10 then true
else false
```

```reasonML
let booleanValue: bool = if (number == 1) {
  true
} else if (number == 10) {
  true
} 
else {
  false
} 
```