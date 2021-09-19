// p5js 
// hat.script
// k.r.bergerstock @20210815

function setup() {
  createCanvas(680, 480);
}

function draw() {
  background(0);
  stroke(160,64,64);
  strokeWeight(1);
  
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
  
}