/**
 * 获取元素
 * @param {string} id 元素ID
 * @returns {HTMLElement | null} 返回元素对象
 */
function my$(id) {
    return document.getElementById(id);
}

// 获取各元素，方便操作
var box = my$("box");
var inner = box.children[0];
var ulObj = inner.children[0];
var list = ulObj.children;
var olObj = inner.children[1];
var arr = my$("arr");
var left = my$("left");
var right = my$("right");
var imgWidth = inner.offsetWidth;
var pic = 0;

// 根据li个数，创建小按钮
for (var i = 0; i < list.length; i++) {
    var liObj = document.createElement("li");
    olObj.appendChild(liObj);
    liObj.innerText = (i + 1);
    liObj.setAttribute("index", i);

    // 为按钮注册mouseover事件
    liObj.onmouseover = function () {
        for (var j = 0; j < olObj.children.length; j++) {
            olObj.children[j].removeAttribute("class");
        }
        this.className = "current";
        pic = this.getAttribute("index");
        animate(ulObj, -pic * imgWidth);
    };
}

// 设置ol中第一个li有背景颜色
var timeId = setInterval(onmouseclickHandle, 3000);

// 左右焦点实现点击切换图片功能
box.onmouseover = function () {
    arr.style.display = "block";
    clearInterval(timeId);
};
box.onmouseout = function () {
    arr.style.display = "none";
    timeId = setInterval(onmouseclickHandle, 3000);
};


right.onclick = onmouseclickHandle;
left.onclick = function () {
    if (pic == 0) {
        pic = list.length - 1;
        animate(ulObj, -pic * imgWidth);
    } else {
        pic--;
        animate(ulObj, -pic * imgWidth);
    }
    syncIndicator(olObj, pic);
};

window.onload = function() {
    syncIndicator(olObj, pic);
};

function onmouseclickHandle() {
    if (pic == list.length - 1) {
        pic = 0;
        animate(ulObj, 0);
    } else {
        pic++;
        animate(ulObj, -pic * imgWidth);
    }
    syncIndicator(olObj, pic);
}

// 同步指示器
function syncIndicator(olObj, pic) {
    for (var i = 0; i < olObj.children.length; i++) {
        olObj.children[i].removeAttribute("class");
    }
    olObj.children[pic].className = "current";
}

// 设置任意的一个元素,移动到指定的目标位置
function animate(element, target) {
    clearInterval(element.timeId);
    var start = element.offsetLeft;
    var change = target - start;
    var duration = 1500; // 动画持续时间1.5秒
    var startTime = performance.now();

    function step() {
        var currentTime = performance.now();
        var timeElapsed = currentTime - startTime;
        var progress = Math.min(timeElapsed / duration, 1); // 确保进度不超过1
        var current = start + change * progress;
        if (timeElapsed < duration) {
            element.style.left = current + "px";
            requestAnimationFrame(step);
        } else {
            element.style.left = target + "px";
        }
    }
    requestAnimationFrame(step);
}