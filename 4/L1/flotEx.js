$(function () {

var D=[];
var b=0.2; //шаг
for(var x=0; x<=5 ; x+=b){
    D[D.length]=[x,Math.exp(-x)];
}  //точки функции f(x) вычисляются в цикле
  
var FREQ=[];
var CFREQ=[];
var N=10000; //число генерируемых случайных числе
var r;
var k;

for(var j=0;j<10;j++){
	FREQ[j]=0;
} //инициализация массива FREQ

for(var i=0;i<N;i++){
	r=Math.random() //генерация псевдослучайных чисел
	while(r==0){
		r=Math.random();
	}

r=-Math.log(r);
k=9;
for(var j=0;j<10;j++){
	if(k==9) if(r<= (0.5*(j+1))) k=j;  //находится номер подинтервала k
} //генерация псевдослучайного числа, распределенного экспоненциально

FREQ[k]++;
} //подсчет частот попадания в подинтервалы


CFREQ[0]=FREQ[0]/N;
for(var i=1;i<10;i++) {
	CFREQ[i]=FREQ[i]/N+CFREQ[i-1];
}
for(var i=0;i<10;i++){
	FREQ[i]=[i*0.5,FREQ[i]/N];
	CFREQ[i]=[i*0.5,CFREQ[i]];
}


$.plot($("#placeholder"),[
{
	data: D,
	label:"f(x)=exp(-x)",
	points:{show:true},
	lines:{show:true,fill:false}
},

{
	data: FREQ,
	label:"Относительные частоты",
	bars:{show:true, barWidth:0.5}
	  },


  {
  	data:CFREQ,
  	label:"Накопительные частоты",
  	lines:{show:true,steps:true}
  },


{
	legend:{position:"nw"}
}
]);

});


