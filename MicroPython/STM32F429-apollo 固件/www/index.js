var i = 0;
//定义函数：构建要显示的时间日期字符串
function showTime()
{
 //创建Date对象
 var today = new Date();
 //分别取出年、月、日、时、分、秒
 var year = today.getFullYear();
 var month = today.getMonth()+1;
 var day = today.getDate();
 var hours = today.getHours();
 var minutes = today.getMinutes();
 var seconds = today.getSeconds();
 //如果是单个数，则前面补0
 month  = month<10  ? "0"+month : month;
 day  = day <10  ? "0"+day : day;
 hours  = hours<10  ? "0"+hours : hours;
 minutes = minutes<10 ? "0"+minutes : minutes;
 seconds = seconds<10 ? "0"+seconds : seconds;
  
 //构建要输出的字符串
 var str = year+"年"+month+"月"+day+"日 "+hours+":"+minutes+":"+seconds;

 $("#getTime").html(str);
 //延时器
 window.setTimeout("showTime()",1000);
}

    function formatBool(val) {
        return val == 0 ? '否' : val == 1 ? '是' : '未知';
    }

    function formatInt(num) {
        var result = parseFloat(num);

        if (isNaN(result)) {
        alert('传递参数错误，请检查！');
        return false;
        }
        result = Math.round(num * 100) / 100;
        var s_x = result.toString();
        var pos_decimal = s_x.indexOf('.');
        if (pos_decimal < 0) {
        pos_decimal = s_x.length;
        s_x += '.';
        }
        while (s_x.length <= pos_decimal + 2) {
        s_x += '0';
        }
        return s_x;   

       }

       function formatPercent(val) {
        var num = formatInt(val);
        return num + "%" ;
    }

    function getInfo() {
        showTime()
        $.ajax({
            url: "http://" + location.hostname + "/sysdata",
            method: "GET"
        })
            .success(function (result) {
                if(result && result.body && result.body.result){
                var _result = result.body.result 
                $("#versions").html(_result.versions);
                $("#ipAddress").html(_result.ipAddress);
                $("#cpuUtilization").html(formatPercent(_result.cpuUtilization));
                $(".sr-only").css("width",formatPercent(_result.cpuUtilization));
                $("#mag_x").html(formatInt(_result.Magnetometer.mag_x));
                $("#mag_y").html(formatInt(_result.Magnetometer.mag_y));
                $("#mag_z").html(formatInt(_result.Magnetometer.mag_z));
                $("#accel_x").html(formatInt(_result.Acceleration.accel_x));
                $("#accel_y").html(formatInt(_result.Acceleration.accel_y));
                $("#accel_z").html(formatInt(_result.Acceleration.accel_z));
                var i = parseInt(i)+1;
                console.log("获取第"+i+"次数据")
                console.log(_result)
                }                          
            })
            
            .complete(function () {
                window.setTimeout("getInfo()",1000);
            })
            
            .error(function () {
            })
    }
    window.onload = getInfo()