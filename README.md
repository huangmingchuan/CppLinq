#CppLinq
用 C++ 11 实现的 LINQ to Object，这里有篇粗浅的[文章](http://www.cnblogs.com/huangmingchuan/p/4988821.html)来介绍：

###一个例子：
```
class person
{
    string name;
};

class pet
{
    string name;
    person owner;
};

person magnus = { "Hedlund, Magnus" };
person terry = { "Adams, Terry" };
person charlotte = { "Weiss, Charlotte" };
person persons[] = { magnus, terry, charlotte };
pet barley = { "Barley", terry };
pet boots = { "Boots", terry };
pet whiskers = { "Whiskers", charlotte };
pet daisy = { "Daisy", magnus };
pet pets[] = { barley, boots, whiskers, daisy };
```
