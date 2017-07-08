# MiniPhotoShop
A light and simple mini photoshop.

# Update Logs
- 直线，椭圆，画笔颜色，画笔粗细 `1.0`
# Attentions
1. 开发在dev分支上进行，master分支为发布分支，新版本开发完毕提交PR，由管理员code review后merge，随后自动集成到服务器。
2. 如果使用Cmake编译，请复制一份CMakeLists.txt.example，然后将其`.example`去掉。接下来直接运行`cmake .`命令即可生成`makefile`
3. 如果使用其他IDE编译，请不要破坏文件结构，并将IDE自动生成的代码无关的文件夹及文件加入到.gitignore中。例如使用Clion编译会产生.idea文件夹，现已将其加入到.gitignore中。
