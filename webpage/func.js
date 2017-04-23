function compute(outlook, temp, wind, season, humidity) {
let features = [];
features[0] = {
"heavy snow": 8,
"light snow": 7,
"heavy rain": 6,
"rain": 5,
"overcast": 0,
"light rain": 4,
"cloudy": 1,
"clear": 2,
"haze": 3,
}[outlook];
if (typeof features[0] === 'undefined') {
throw new Error('Invalid value in variable outlook: ' + JSON.stringify(outlook));
}
if (temp < 30.000000) {features[1] = 0;}
else if (temp < 40.000000) {features[1] = 1;}
else if (temp < 50.000000) {features[1] = 2;}
else if (temp < 60.000000) {features[1] = 3;}
else if (temp < 70.000000) {features[1] = 4;}
else {features[1] = 5;}
if (wind < 2.000000) {features[2] = 0;}
else if (wind < 4.000000) {features[2] = 1;}
else if (wind < 6.000000) {features[2] = 2;}
else if (wind < 10.000000) {features[2] = 3;}
else {features[2] = 4;}
features[3] = {
"summer": 2,
"fall": 3,
"spring": 1,
"winter": 0,
}[season];
if (typeof features[3] === 'undefined') {
throw new Error('Invalid value in variable season: ' + JSON.stringify(season));
}
if (humidity < 40.000000) {features[4] = 0;}
else if (humidity < 50.000000) {features[4] = 1;}
else if (humidity < 60.000000) {features[4] = 2;}
else if (humidity < 70.000000) {features[4] = 3;}
else if (humidity < 80.000000) {features[4] = 4;}
else {features[4] = 5;}
let data = [
[[20, 10, 68, 2, 11, 5, 1, 1, ], [4, 13, 16, 36, 15, 34, ], [1, 24, 49, 35, 9, ], [29, 28, 29, 32, ], [8, 26, 28, 25, 23, 8, ], [118, ], ],
[[33, 16, 58, 1, 9, 7, 2, 1, 1, ], [4, 10, 24, 27, 24, 39, ], [3, 34, 53, 34, 4, ], [33, 33, 33, 29, ], [6, 17, 33, 35, 23, 14, ], [0, 128, ], ],
];
let max_prob = 0;
let max_val;
data.forEach(function(result, i) {
    let total = result[5][i];
    let prob = total / 246;
    result.forEach(function(histogram, j) {
        if (j == 5) {return;}
        prob *= histogram[features[j]] / total;
    });
    if (prob > max_prob) {
        max_prob = prob;
        max_val = i;
    }
});
result = {
"1": "down",
"0": "up",
}[max_val];
if (typeof result === 'undefined') {
throw new Error('Invalid value in variable max_val: ' + JSON.stringify(max_val));
}
return result;
};

