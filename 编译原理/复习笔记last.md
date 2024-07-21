# 10语法制导翻译和中间代码生成

**布尔表达式的四元式**  老师原话：考试很大概率考这个。每次考试都会考。产生四元式的过程、翻译的过程、回填的过程。truelist和falseflist的编号、分析树。产生的四元式，包括回填。

![image-20240626103114226](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626103114226.png)

![image-20240626103130687](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626103130687.png)

大概就是这两类的，能跟着ppt上的对应的动作把四元式生成出来。注意理解chain和backpatch的作用，回填







语法制导生成后缀式子

![image-20240605104954654](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240605104954654.png)

将输入一个个读入栈，根据上面的规则改变栈内值和更新输出，可得到后缀式输出





# 11符号表

![image-20240626114026443](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626114026443.png)

![image-20240626114111804](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626114111804.png)

![image-20240626114134089](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626114134089.png)

![image-20240626114400211](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626114400211.png)

![image-20240626120759574](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626120759574.png)

TOP：栈符号表的栈顶指针、栈顶的第一个可用单元

SP：指向当前正在处理的最内层过程的子表在栈符号表中的起始位置。

栈符号表中 name指变量名 previous指下一个变量名的位置，为0表示一个过程结束，display标志的值代表对应过程在栈符号表中的起始位置

![image-20240626121213989](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626121213989.png)

![image-20240626121421190](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626121421190.png)

# 12运行时存储空间组织

![image-20240626160513232](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626160513232.png)

![image-20240626161008352](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626161008352.png)

main中的访问链：100，置为空

main中的控制链：099，置为空。

后面也是 先访问链（本过程的非局部变量访问指针）后控制链（指向调用者活动记录的指针）

一般由fp指向控制链	

![image-20240626162056679](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626162056679.png)

每个过程的fp指针代表该过程，一般fp指针指向控制链的位置

![image-20240626162954742](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240626162954742.png)

整体最上面是静态变量、全局变量；局部最上面是参数，中间是（访问链+控制链+返回地址），下面是局部变量。

当参数包含过程时 procedure bar(procedure t; var x :integer);

9	t[1]:t@label

8	t[0]:xx	（定义此过程的对应过程的控制链）

7	<参数2>：后面的数值

6	<参数1>: 8

5	访问链	定义此过程的过程的控制链

4	控制链 调用此过程的过程的控制链

3	返回地址

注意参数倒着写

如果要写sp，sp在局部变量区域最小的数字对应的栈空间

##### 传递数组为参数的例子

![image-20240627105620207](https://gitee.com/du-jianyu1012/img/raw/master/picture/image-20240627105620207.png)