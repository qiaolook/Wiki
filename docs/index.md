---
title: 首页 
comments: true
---

!!! info "本技术库目前仅包含我所负责的电控部分"

我们这届的作品并不算完善，因为无论是电控还是机械结构设计，几乎都是从零起步。

**机械方面**：需要朝着更易维修、结构更合理的方向改进，并提升制造精度——因为机械结构的上限直接决定了最终能调出的精度。

**电控方面**：由于我的程序采用裸机开发，运行效率受限，主循环中几乎不能添加额外逻辑，否则会影响实时性，造成小车不稳定。未来建议大家使用 **FreeRTOS** 实时操作系统，以提升程序的稳定性与可维护性。

**视觉方面**：YOLOv5Lite 在物体识别上较为准确，但在找中心点时稳定性不足。虽然我将滤波改为卡尔曼滤波，效果有所提升，但整体反馈误差比较抽象，后续需要进一步改进算法。

___做项目不是凭空想象、闭门造车就能做好的，所以多去了解别人的设计思路和经验，吸取别人的优点。不要固步自封，一定要勇于尝试和创新。___

!!! quote "建议参考 up 主 [空城少年_Space](https://space.bilibili.com/351768796) 的 [硬件与电控](https://blog.csdn.net/m0_74056439/article/details/150104661)、[机械设计](https://blog.csdn.net/louisaerdusai/article/details/150106890) 和 [视觉方案](https://blog.csdn.net/2303_80277100/article/details/150211965) 。"



!!! warning "注意"

    本技术库的代码和文档均在 [GitHub](https://github.com) 上托管，因 GitHub 服务器位于国外，如果加载速度较慢，请尝试使用例如 [Clash Verge](https://github.com/clash-verge-rev/clash-verge-rev) 等网络代理工具。

    由于我个人精力有限，**文档和代码可能存在错误或不完善之处**。若发现问题，欢迎提交 [issues](https://github.com/qiaolook/Wiki/issues) 或评论区留言。

---
