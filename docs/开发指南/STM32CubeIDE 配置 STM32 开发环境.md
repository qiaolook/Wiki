STM32CubeIDE 配置 STM32 开发环境非常简单，只需要下载安装 STM32CubeIDE 即可。但是使用时需要注册 ST 账户，因为Cube MX 需要联网下载芯片固件包，且下载软件也需要 ST 账户。
>ST 官网的网速十分的感人，建议使用网络代理工具。

- [STM32CubeIDE 下载链接](https://www.st.com.cn/zh/development-tools/stm32cubeide.html)

安装过程没有什么困难，直接无脑下一步即可，__但注意在安装程序安装 ST-Link 时候会弹窗，不要点取消，否则不能烧录程序__。

主要是汉化的问题，按网上教程汉化后，主页会显示乱码，建议按照我下面提供的步骤汉化。

----
- 打开 Install New Software 界面

![打开Install New Software界面.png](%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.assets/%E6%89%93%E5%BC%80Install%20New%20Software%E7%95%8C%E9%9D%A2.png))

----
- 在顶部点击 Add

![在顶部点击 Add.png](%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.assets/%E5%9C%A8%E9%A1%B6%E9%83%A8%E7%82%B9%E5%87%BB%20Add.png)

----
- 输入清华大学的`babel`软件源，名字随便取

```
https://mirrors.tuna.tsinghua.edu.cn/eclipse/technology/babel/update-site/latest/
```

![输入清华大学的babel软件源，名字随便取.png](%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.assets/%E8%BE%93%E5%85%A5%E6%B8%85%E5%8D%8E%E5%A4%A7%E5%AD%A6%E7%9A%84babel%E8%BD%AF%E4%BB%B6%E6%BA%90%EF%BC%8C%E5%90%8D%E5%AD%97%E9%9A%8F%E4%BE%BF%E5%8F%96.png)

----
- 加载完之后就会有这样一些项目出现，务必要按照下面的指示选择，不能多选，因为有一些选项选上了就会导致主页崩溃

![1.png](%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.assets/1.png)

![2.png](%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.assets/2.png)

----
- 然后点击 next 即可按照正常步骤汉化操作。汉化过后主页是这样的

![3.png](%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.assets/3.png)