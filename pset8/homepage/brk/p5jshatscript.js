// p5js 
// hat.script
// k.r.bergerstock @20210815

var kanvas;
var colorPicker;

function centerKanvas(){
  var cx = (500);
  var cy = (200);
  kanvas.position(cx,cy);
  colorPicker.position(65,300);
}

function setup() {
  kanvas = createCanvas(680, 480);
  colorPicker = createColorPicker('#A04040');
  centerKanvas();
  textSize(14);
}

function windowResized(){
  centerKanvas();
}

function draw() {
  background(0);
  stroke(colorPicker.value());
  strokeWeight(1);
  var start = performance.now();
  // defined constants
  let pi = 3.14159265358979323846;
  let XP = 300.0;
  let YP = 110.0;
  let ZP = 90.0;
  let XR = (1.5 * pi);
  let YR = 1.0;
  // function variables
  let xf = XR / XP;
  let yf = YP / YR;
  let zf = XP / ZP;
  let xp2 = XP * XP;

  let cx = 680 / 2;
  let cy = 480 / 2 * 9 / 10;

    for( let zi = -ZP; zi < ZP; zi++)
    {
        let zt = zf * zi;
        let xl = round(0.5 + sqrt(xp2 - (zt * zt)));
        for (let xi = -xl; xi <= xl; xi += 2)
        {
            let xt = sqrt(xi * xi + zt * zt) * xf;
            let yy = sin(sin(xt) + 0.4 * sin(3.0 * xt)) * yf;
            let sx = (cx + xi + zi);
            let sy = (cy + zi - yy);
            point(sx, sy);
        }
    }
    var elapsed = int(performance.now() - start);
    var msg = 'Elapsed time: ';
    fill(colorPicker.value());
    text(msg,5,25);
    text(elapsed.toString(),95,25);
}