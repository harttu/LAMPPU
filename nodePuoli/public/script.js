
var led = function(Xarray,variArray,valintaArray) {
  this.X = Xarray;
  this.vari = variArray;
  this.valinta = valintaArray;
};

var ledi1 = new led([0,150,300,450,600],["#000000","#ffffff","#12f445","#f31200","#000000"],[1,1,0,0,1]);
var ledi2 = new led([0,150,300,450,600],["#ffffff","#000000","#ff00ff","#121223","#ffffff"],[1,0,0,0,1]);
var ledi3 = new led([0,150,300,450,600],["#123456","#ff3300","#123412","#000000","#1223aa"],[1,0,0,0,1]);
var ledi4 = new led([0,150,300,450,600],["#435465","#ff3300","#566aaa","#0a0f00","#1223aa"],[1,0,0,0,1]);

var ledit = [ledi1,ledi2,ledi3,ledi4];

console.log("ALUSTUKSEN JALKEEN:"+ledi1.valinta[0])
var c = document.getElementById("myCanvas");
var ctx = c.getContext("2d");

paivitaCanvas(ctx,ledit);

function paivitaCanvas(ctx,ledit){
	for(var i = 0; i < ledit.length; i++) {
  	piirraLedi(ctx,ledit[i],i); }
}

function muutaLedienVarit(ledit,vari){
	for( var i = 0; i < ledit.length; i++ ) {
		for( var j = 0; j < ledit[i].valinta.length; j++ ) {
      if( ledit[i].valinta[j] === 1 ) {
      	console.log("				Muutan ledit "+i+" kohdan "+j+" arvoa");
    		ledit[i].vari[j] = '#'+vari;
        console.log("				Se on nyt "+ledit[i].vari[j]);
      }
    }
  }
}

function piirraLedi(ctx,ledi,lediNumero){
  for( var i = 0; i < ledi.X.length - 1; i++ ){
      console.log("	Piirretaan gradientti")
      // Piirrä gradientti
      if( ledi.valinta[i] === 2 ) {
        console.log("		Skipataan tämä kierros")
        piirraPystyViiva(ledi.X[i],105 * lediNumero,ledi.vari[i],ledi.valinta[i]); // Piirretään pystyviiva
        continue;} // Skipataan loppukierros
      // etsitaan seuraava päätepiste
      var paatePiste = i;
      console.log("		Etsitaan paatepiste kohdalle:"+i)
      for(var g = i + 1; g < ledi.X.length; g++) {
        if( ledi.valinta[g] !== 2 ) { // päätepiste löydetty
          paatePiste = g;
          console.log("		Paatepiste löydetty kohdasta:"+paatePiste)
          break;
        }
      }
      // piirretaan gradientti i:stä päätepisteeseen;
      piirraGradientti(ledi.X[i],ledi.X[paatePiste],105 * lediNumero,ledi.vari[i],ledi.vari[paatePiste]);
      if( i === 0 ) 
        piirraPystyViiva(2,105 * lediNumero,ledi.vari[i],ledi.valinta[i]);
      else  
        piirraPystyViiva(ledi.X[i],105 * lediNumero,ledi.vari[i],ledi.valinta[i]);
   }
   var e = ledi.X.length - 1;
   console.dir(ledi.X)
   console.log("######################"+ledi.X[e]);
   piirraPystyViiva(ledi.X[e] - 2,105 * lediNumero,ledi.vari[e],ledi.valinta[e]);
    
    
}
function piirraGradientti(alku,loppu,yPos,alkuVari,loppuVari) {
//		console.log("		Piirretaan gradientti arvolla alkuVari "+alkuVari+" loppuVari "+loppuVari)
 //   var grd = ctx.createLinearGradient(alku, 0, alku + 150, 0);
    var grd = ctx.createLinearGradient(alku, 0, loppu , 0);
    grd.addColorStop(0, alkuVari);
    grd.addColorStop(1, loppuVari);
    ctx.fillStyle = grd;
    						//x0	 y0   x_mitta					   y_mitta
    ctx.fillRect(alku, yPos, loppu - alku,		 100 );
    //console.log("		piirraGradientti kutsuttu alkuVari:"+alkuVari+" & loppuVari:"+loppuVari)
}


function piirraPystyViiva(x,yPos,vari,valinta){
      ctx.beginPath();
//	if( x=== 0) { x = 5; }
//	if( x === 600) { x = 595; }
//      console.log("				Valinta on "+valinta)
      if( valinta === 0) { // viivaa ei ole klikattu
        /*if( vari === "red" ) 
          ctx.strokeStyle = "black"; 
         else*/
         ctx.strokeStyle = "red";
			}
      else if( valinta === 2 ){
      	ctx.strokeStyle = "black";
//        ctx.lineWidth = 2;
      }
      else { // viiva on valittu
          ctx.strokeStyle = "white"; 
 			}
			ctx.moveTo(x, yPos);
      ctx.lineTo(x, yPos +100 );
      ctx.stroke();
}

var mouseX = 0;
var mouseY = 0;


// Update Mouse Position on click
$("#myCanvas").on('click', function(e){
    mouseX = e.pageX - c.offsetLeft;
    mouseY = e.pageY - c.offsetTop;
    var x = Math.round(mouseX/150,1);
    var y = Math.floor(mouseY/105,1);
    console.log("X:"+x)
    console.log("Y:"+y)
    if( !ledit[y] ) {}
    else if( ledit[y].valinta[x] === 0 )
        ledit[y].valinta[x] = 1;
    else
        ledit[y].valinta[x] = 0;
    //console.dir(ledit[0].valinta);
    paivitaCanvas(ctx,ledit);
    
		var bla = $('#color').val();
    console.log("BLA:"+bla)
});


// Update Mouse Position on click
$("#myCanvas").on('dblclick', function(e){
	console.log("Kaksoisklikkaus");
    mouseX = e.pageX - c.offsetLeft;
    mouseY = e.pageY - c.offsetTop;
    var x = Math.round(mouseX/150,1);
    var y = Math.floor(mouseY/105,1);
    console.log("X:"+x)
    console.log("Y:"+y)
    if( !ledit[y] ) {}
    else {
    // valitaan tämä vihreäksi
    	ledit[y].valinta[x] = 2;
    }
    console.dir(ledit[0].valinta);
    
    paivitaCanvas(ctx,ledit);
});

$("#ledSync").click(()=>{
console.log("AJAX serverille");
var data = JSON.stringify(ledit);
console.log("datan:"+data);
$.ajax({
  type: "POST",
  url: 'http://localhost:3333/sync',
  data: {ledit: data},
  success: function (result) {
        console.log(result);
        if(result.status == 200){
            self.isEditMode(!self.isEditMode());
        }
    },
  dataType: 'application/json'//dataType
});
})


var vanhaVari = $('#color').val();

setInterval(function(){ 
	var uusiVari = $('#color').val();
  if( vanhaVari !== uusiVari ) {
  	console.log("MUUTETAAN LEDIT");
    muutaLedienVarit(ledit,uusiVari);
    console.log("------------->"+ledit[0].vari[0])
    paivitaCanvas(ctx,ledit);
    console.dir(ledit[0]);
   } 
  vanhaVari = uusiVari;
   
}, 1000);
    /*        
function laskeKeskiVari(vasen,oikea){
        var RvasenS = vasen[1] + vasen[2];
        var GvasenS = vasen[3] + vasen[4];
        var BvasenS = vasen[5] + vasen[6];
        
        var RvasenI = parseInt(RvasenS,16);
        var GvasenI = parseInt(GvasenS,16);
        var BvasenI = parseInt(BvasenS,16);
        
        var RoikeaS = oikea[1] + oikea[2];
        var GoikeaS = oikea[3] + oikea[4];
        var BoikeaS = oikea[5] + oikea[6];

				var RoikeaI = parseInt(RoikeaS,16);
        var GoikeaI = parseInt(GoikeaS,16);
        var BoikeaI = parseInt(BoikeaS,16);
        
				var RuusiS = Math.floor( (RvasenI + RoikeaI) / 2 ).toString(16);
				var GuusiS = Math.floor( (GvasenI + GoikeaI) / 2 ).toString(16);
				var BuusiS = Math.floor( (BvasenI + BoikeaI) / 2 ).toString(16);
				
				console.log("RuusiS:"+RuusiS);        
        return '#'+RuusiS+GuusiS+BuusiS;
      }*/
