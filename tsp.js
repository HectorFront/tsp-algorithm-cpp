console.time('timer-tsp');
let originCoords = [-23.5505, -46.6333]; // cd

let coords = [
  [-15.7938, -47.8827],
  [-3.7172, -38.5433],
  [-12.9714, -38.5014],
  [-22.9068, -43.1729],
  [-3.1190, -60.0217],
  [-16.6868, -49.2648],
  [-8.0476, -34.8770],
  [-25.4296, -49.2711],
  [-30.0346, -51.2177],
  [-19.9167, -43.9345],
  [-10.1833, -48.3333],
  [-5.0892, -42.8019],
  [-2.5307, -44.3068],
  [-15.5961, -56.0969],
  [-6.1843, -36.5746],
  [-28.2667, -52.4167],
  [-13.5000, -50.5000],
  [-9.5000, -65.5000],
  [-21.5000, -45.5000]
];

const REarth = 6371;

function distanceLatLng(p1, p2) {
  let [lat1, lng1] = p1;
  let [lat2, lng2] = p2;

  let dLat = (lat2 - lat1) * Math.PI / 180;
  let dLng = (lng2 - lng1) * Math.PI / 180;
  let a = Math.sin(dLat/2) * Math.sin(dLat/2) +
          Math.cos(lat1 * Math.PI / 180) * Math.cos(lat2 * Math.PI / 180) *
          Math.sin(dLng/2) * Math.sin(dLng/2);
  let c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
  return REarth * c;
}

let tspDistances = [originCoords];

for (let i = 0; i < coords.length; i++) {
    if (tspDistances.length == 0){
        tspDistances.push(coords[i]);
    } else {
        let minDistance = Infinity;
        let closestCoord;
        for (let j = 0; j < coords.length; j++) {
            if (coords[j] != coords[i]){
                let dist = distanceLatLng(coords[i], coords[j]);
                if (dist < minDistance) {
                    minDistance = dist;
                    closestCoord = coords[j];
                }
            }
        }
        tspDistances.push(closestCoord);
    }
}

console.log(tspDistances);
console.timeEnd('timer-tsp');