##环境是mac

####一、安装emsdk 
1、git clone https://github.com/emscripten-core/emsdk.git  
2、cd emsdk
3、./emsdk install latest
4、./emsdk activate latest
5、source ./emsdk_env.sh

####二、C代码(main.cpp)  
```c
#include <emscripten.h>  
extern "C"  {  
    EMSCRIPTEN_KEEPALIVE  
    const char* reply(const char* chr) {  
        return "hi man";  
    }  
};  
```

####三、html代码(index.html)  
```javascript
<!DOCTYPE html>  
<html>  
<head>  
    <script src="./main.js"></script>  
    <input type="text"  id="showtext" >  
</body>  
</html>    
<script type="text/javascript">  
(function() {  
	Module.onRuntimeInitialized = function() {  
		var input = "hello";   //生成字符串  
		var input_ptr = allocateUTF8(input);  //生成字符串的指针  
		var retPtr = Module._reply(input_ptr);  //调用c方法  
		var resValue = UTF8ToString(retPtr);  //将返回指针转成字符串  
		document.getElementById("showtext").value = resValue;//显示  
		_free(input_ptr);//释放返回指针  
	}  
})();  
</script>
```

####三、编译命令
```shell
emcc main.cpp -std=c++11 -Os  -s WASM=1 -o main.js -s EXPORTED_FUNCTIONS='["_reply"]' -s ASSERTIONS=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["allocateUTF8","intArrayFromString","Pointer_stringify"]'
```

####四、测试  
将编译出来的main.js，index.html，main.wasm拷贝到服务器根目录下
/Library/WebServer/Documents  
运行sudo apachectl start  
浏览器输入localhost看结果



