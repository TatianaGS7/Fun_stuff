function main(){
   document.getElementById("divA").innerHTML=A;
   document.getElementById("divB").innerHTML=B;
   document.getElementById("divL").innerHTML=L;
   document.getElementById("divN").innerHTML=N;
   document.getElementById("divTINT").innerHTML=TINT;
   document.getElementById("divSTEP").innerHTML=STEP.toFixed(3);
   document.getElementById("interval").innerHTML="["+A.toFixed(3)+","+B.toFixed(3)+"]";
}

//Равномерно-распределенные случ. числа на интервале 
var A=0;
var B=1;
var L=B-A;

var N=100000;//Число генерируемых случайных чисел
var NUMBERS=[];//Массив сгенерированных случайных чисел

var TINT=10;//Число подинтервалов, на которое делится [A,B]
var HIST=[];//Границы подинтервалов
var FREQ=[];//Таблица частот(число попаданий в каждый подинтервал

var MAX=A;//Максимальное случайное число
var MIN=B;//Минимальное случайное число
var AVE=0;//Среднее значение
var DISP=0;//Дисперсия
var SIGMA=0;//Стандартное отклонение

//Вспомогательные переменные
var STEP=L/TINT; //Длина подинтервала
var R=0;

function startAndShow(){
   var r;
   var step=(B-A)/TINT;
   STEP=step;
   MAX=A;
   MIN=B;
   AVE=0;
   HIST=[];
   FREQ=[];
   HIST[0]=A;
   FREQ[0]=0;
   for(var i=1;i<TINT;i++){
      HIST[i]=HIST[i-1]+step;
      FREQ[i]=0;
   }
   SUM=0;
   SUMSQR=0;
   NUMBERS=[];
   for(var i=0;i<N;i++){
      r=generate();//генерируется случайное число
      SUM+=r;
      SUMSQR+=r*r;
      if(r>MAX) MAX=r;
      if(r<MIN) MIN=r;
      NUMBERS[i]=r;
   }
   AVE=SUM/N;//Вычисление среднего
   DISP=SUMSQR/(N-1)-(N-1)/N*AVE*AVE;//Вычисление дисперсии
   SIGMA=Math.sqrt(DISP);//Вычисление стандартного отклонения
   showStat();
   dencity();
}

function showStat(){
//Отображение числовых характеристик последовательности 
   var s="<h2>Вычисленные характеристики последовательности</h2>";
   s+="<table  border='1'>";
   s+="<tr>"+"<td>"+"A:"+"</td><td>"+A.toFixed(4)+"</td></tr>";
   s+="<tr>"+"<td>"+"B:"+"</td><td>"+B.toFixed(4)+"</td></tr>";
   s+="<tr>"+"<td>"+"L:"+"</td><td>"+L.toFixed(4)+"</td></tr>";
   s+="<tr>"+"<td>"+"N:"+"</td><td>"+N+"</td></tr>";
   s+="<tr>"+"<td>"+"MAX:"+"</td><td>"+MAX.toFixed(4)+"</td></tr>";
   s+="<tr>"+"<td>"+"MIN:"+"</td><td>"+MIN.toFixed(4)+"</td></tr>";
   s+="<tr>"+"<td>"+"AVE:"+"</td><td>"+AVE.toFixed(4)+"</td></tr>";
   s+="<tr>"+"<td>"+"DISP:"+"</td><td>"+DISP.toFixed(4)+"</td></tr>";
   s+="<tr>"+"<td>"+"SIGMA:"+"</td><td>"+SIGMA.toFixed(4)+"</td></tr>";
   s+="</table>";
   s+="<h3>График рассеяния</h3>"
   s+="Построен для N/2 = "+(N/2)+" пар точек {NUMBERS[i],NUMBERS[i+1]},i=0,(2),N-2;"+"<br/>";
   s+='<br/><canvas id="canvas" width="401" height="401"></canvas><br/>'
   s+="<br/><input type='button' value='построить гистограмму' onclick='showHist()'/>";
   s+="<br/><div id='histTab'></div>";
  
   document.getElementById("mytab").innerHTML = s;
}
var CTX,H,W;
function dencity(){
//График рассеяния
var scale=1/(MAX-MIN);
   var d=document.getElementById("canvas");
   CTX=d.getContext("2d");
   H=d.height;
   W=d.width;
   CTX.strokeRect(0,0,W,H);
   CTX.fillStyle="red";
   for(var i=0;i<N;i+=2){
      CTX.fillRect(W*scale*(NUMBERS[i]-MIN),H*scale*(NUMBERS[i+1]-MIN),0.5,0.5);
   }
}

function showHist(){
//Отображение таблицы частот
   STEP=(B-A)/TINT;
   var step=STEP;
   countHist();
   var sum=0;
   var s='<h2>Таблица частот'+"</h2>";
   s+="ОБОЗНАЧЕНИЯ:"+"<br/>";
   s+="i - номер подинтервала"+"<br/>";
   s+="a(i) - начальная точка подинтервала i"+"<br/>";
   s+="b(i) - конечная точка подинтервала i"+"<br/>";
   s+="n(i) - число(частота) попаданий случайной величины в подинтервал i"+"<br/>";
   s+="p(i)=n(i)/N - относительная частота попадания случайной величины в подинтервал i"+"<br/><br/>";
   s+="<table  border='1'>";
   s+="<tr>"+"<td>"+"i"+"</td><td>"+"a(i)"+
         "</td><td>"+"b(i)"+"</td><td>"+"n(i)"+"</td><td>p(i)</td></tr>";
   for(var i=0;i<TINT;i++){
      s+="<tr>"+"<td>"+(i+1)+"</td><td>"+HIST[i].toFixed(4)+
         "</td><td>"+(HIST[i]+step).toFixed(4)+"</td><td>"+FREQ[i]+"</td><td>"+(FREQ[i]/N).toFixed(4)+"</td></tr>";
      sum+=FREQ[i];
   }
   s+="<tr>"+"<td>"+"</td><td>"+
         "</td><td>"+"</td><td>"+sum+"</td><td></td></tr>";
   s+="</table><br/>";
   s+="<div id='graphic' style='width: 600px; height: 300px;'></div>";
   document.getElementById("histTab").innerHTML=s;
   draw();
}

function countHist(){
//Вычисление числа (частот) попаданий в подинтервалы
   var j;
   for(var i=0;i<TINT;i++){
      FREQ[i]=0;
   }
   for(var i=0;i<N;i++){
      j=countInt(A,B,STEP,NUMBERS[i]);
      if(j>=0) if (j<TINT) FREQ[j]++;
   }
}

function countInt(a,b,step,r){
//Вычисление номера подинтервала, в который попадает случайное число
   if(r<a) return -1;
   if(r>b) return TINT;
   var x=a;
   for(var i=0;i<TINT;i++){
      x+=step;
      if(r<=x) return i;
   }
   return -888;
}


function generate(){
//Генератор случайных чисел, равномерно распределенных на [A,A+L]
   return Math.random()*(L-A)+A;
}

function draw()
{
    var tmp = new Array();
    for (var i=0; i < TINT; i++)
        tmp.push( [i, FREQ[i]] );
    
	var series = [
	{
        data: tmp,
        label: "Количество попаданий в интервал"
    } ];
    
    var options =
    {
        bars:
        {
            show: true,
        }
    };

	$.plot("#graphic", series, options);
}
