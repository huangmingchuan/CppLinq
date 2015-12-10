#CppLinq
用 C++ 11 实现的 LINQ to Object，这里有篇粗浅的[文章](http://www.cnblogs.com/huangmingchuan/p/4988821.html)来介绍：

###一个例子：
```C++
class person
{
    string name;
};

class pet
{
    string name;
    person owner;
};
person fek = { "尔康, 福" };

person ylc = { "良辰, 叶" };
person hmj = { "美景, 花" };
person lks = { "看山, 刘" };
person lat = { "傲天, 龙" };
person persons[] = { ylc, hmj, lks, lat};

pet dog = { "斯派克", ylc };
pet cat = { "汤姆", ylc };
pet mouse = { "杰瑞", hmj };
pet bird = { "愤怒的小鸟", lks };

pet pig = { "风口上的猪", fek };
pet pets[] = { dog, cat, mouse, bird, pig };
```


