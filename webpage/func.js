function compute(outlook, temp, wind, season, humidity) {
let features = [];
features[0] = {
"snow": 9,
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
let nb_func = function(features) {
let data = [
[[38, 24, 123, 3, 25, 14, 4, 3, 0, 4, ], [11, 29, 35, 59, 37, 67, ], [1, 52, 88, 77, 20, ], [59, 61, 53, 65, ], [11, 53, 66, 46, 44, 18, ], [238, ], ],
[[65, 36, 108, 4, 17, 14, 3, 2, 1, 4, ], [12, 26, 37, 52, 42, 85, ], [4, 57, 107, 76, 10, ], [65, 61, 71, 57, ], [12, 45, 68, 65, 40, 24, ], [0, 254, ], ],
];
return data.map(function(result, i) {
    let total = result[5][i];
    let prob = total / 492;
    result.forEach(function(histogram, j) {
        if (j == 5) {return;}
        prob *= histogram[features[j]] / total;
    });
    return prob;
});
};
let dt_func = function(features) {
let index = (function() {
switch (feature[0]) {
case 0:
switch (feature[1]) {
case 0:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 4:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 1:
switch (feature[3]) {
case 0:
switch (feature[4]) {
case 0:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 1;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 1:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
case 4:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 2:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
case 4:
return 1;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 3:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}default:
throw new Error('Invalid feature[4]': feature[4]);
}case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 2:
switch (feature[4]) {
case 0:
return 0;
case 1:
switch (feature[3]) {
case 0:
return 1;
case 1:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 2:
return 1;
case 3:
return 1;
case 4:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
switch (feature[3]) {
case 0:
return 1;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 5:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 0;
case 4:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}default:
throw new Error('Invalid feature[4]': feature[4]);
}case 3:
switch (feature[2]) {
case 0:
return 0;
case 1:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 0;
case 4:
return 0;
case 5:
switch (feature[3]) {
case 0:
return 1;
case 1:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}default:
throw new Error('Invalid feature[4]': feature[4]);
}case 2:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
case 3:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 4:
return 0;
case 5:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 3:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 1;
case 2:
switch (feature[3]) {
case 0:
return 1;
case 1:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
return 1;
case 4:
switch (feature[3]) {
case 0:
return 1;
case 1:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 5:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 4:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 4:
switch (feature[2]) {
case 0:
return 1;
case 1:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 2:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
return 1;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 5:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
case 3:
return 1;
case 4:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 1;
case 2:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 5:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}default:
throw new Error('Invalid feature[1]': feature[1]);
}case 1:
switch (feature[4]) {
case 0:
return 1;
case 1:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 1;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 4:
switch (feature[2]) {
case 0:
return 1;
case 1:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 5:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}default:
throw new Error('Invalid feature[1]': feature[1]);
}case 2:
switch (feature[3]) {
case 0:
switch (feature[1]) {
case 0:
return 0;
case 1:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 2:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 1:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 1;
case 4:
return 0;
case 5:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 1;
case 4:
return 0;
case 5:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 0;
case 2:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 1;
case 3:
return 1;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 3:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}default:
throw new Error('Invalid feature[1]': feature[1]);
}case 4:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 1;
case 2:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 1;
case 5:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 3:
return 1;
default:
throw new Error('Invalid feature[2]': feature[2]);
}default:
throw new Error('Invalid feature[4]': feature[4]);
}case 2:
switch (feature[2]) {
case 0:
return 1;
case 1:
switch (feature[4]) {
case 0:
return 1;
case 1:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 0;
case 5:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 2:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 1;
case 2:
switch (feature[3]) {
case 0:
return 1;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 4:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 5:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 3:
switch (feature[3]) {
case 0:
return 1;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 4:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 2:
switch (feature[3]) {
case 0:
switch (feature[1]) {
case 0:
return 0;
case 1:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 2:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 3:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 1:
switch (feature[4]) {
case 0:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 0;
case 4:
return 0;
case 5:
return 1;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 1:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 0;
case 5:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 2:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
case 4:
return 1;
case 5:
return 1;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 3:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 1;
case 5:
return 1;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 4:
return 0;
case 5:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 0;
case 4:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}default:
throw new Error('Invalid feature[4]': feature[4]);
}case 2:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
case 3:
return 0;
case 4:
return 0;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 3:
switch (feature[4]) {
case 0:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 1:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 2:
return 0;
case 3:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 1;
case 4:
return 0;
case 5:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 4:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
switch (feature[1]) {
case 0:
switch (feature[4]) {
case 0:
return 1;
case 1:
return 0;
case 2:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 1:
return 0;
case 2:
switch (feature[3]) {
case 0:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 1:
return 0;
case 2:
return 0;
case 3:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
default:
throw new Error('Invalid feature[4]': feature[4]);
}default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
switch (feature[4]) {
case 0:
return 0;
case 1:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 2:
return 0;
case 3:
return 1;
case 4:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 4:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 5:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 0;
default:
throw new Error('Invalid feature[4]': feature[4]);
}default:
throw new Error('Invalid feature[1]': feature[1]);
}case 4:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}default:
throw new Error('Invalid feature[2]': feature[2]);
}case 3:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 5:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}default:
throw new Error('Invalid feature[1]': feature[1]);
}case 4:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
switch (feature[3]) {
case 0:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
case 4:
return 0;
case 5:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 1:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
case 4:
return 1;
case 5:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 2:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 3:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
switch (feature[3]) {
case 0:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 0;
case 5:
return 0;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 3:
return 1;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 1:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 0;
case 5:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 4:
return 1;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 4:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
return 0;
case 4:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}default:
throw new Error('Invalid feature[2]': feature[2]);
}case 5:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 1;
case 2:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 1;
case 3:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}default:
throw new Error('Invalid feature[2]': feature[2]);
}case 3:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
switch (feature[3]) {
case 0:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 1;
case 5:
return 0;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
switch (feature[3]) {
case 0:
return 0;
case 1:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 0;
case 5:
return 0;
default:
throw new Error('Invalid feature[4]': feature[4]);
}case 2:
return 0;
case 3:
return 1;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 4:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 4:
return 0;
case 5:
switch (feature[4]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
case 4:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
switch (feature[3]) {
case 0:
return 0;
case 1:
return 1;
case 2:
return 0;
case 3:
return 0;
default:
throw new Error('Invalid feature[3]': feature[3]);
}case 3:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 5:
return 1;
default:
throw new Error('Invalid feature[4]': feature[4]);
}default:
throw new Error('Invalid feature[1]': feature[1]);
}case 6:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 0;
case 4:
return 0;
case 5:
return 1;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 7:
switch (feature[1]) {
case 0:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
return 0;
case 3:
return 1;
case 4:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}case 1:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 8:
return 1;
case 9:
switch (feature[2]) {
case 0:
return 0;
case 1:
return 0;
case 2:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 0;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 3:
switch (feature[1]) {
case 0:
return 0;
case 1:
return 1;
default:
throw new Error('Invalid feature[1]': feature[1]);
}case 4:
return 0;
default:
throw new Error('Invalid feature[2]': feature[2]);
}default:
throw new Error('Invalid feature[0]': feature[0]);
}})();let res = [];
res[index] = 1.0;
return res;
};
let nb_arr = nb_func(features);
let dt_arr = dt_func(features);
let nb_obj = {};
let dt_obj = {};
nb_res.forEach(function(val, index) {
key = {
"1": "down",
"0": "up",
}[index];
if (typeof key === 'undefined') {
throw new Error('Invalid value in variable index: ' + JSON.stringify(index));
}
nb_obj[key] = val;
});
dt_res.forEach(function(val, index) {
key = {
"1": "down",
"0": "up",
}[index];
if (typeof key === 'undefined') {
throw new Error('Invalid value in variable index: ' + JSON.stringify(index));
}
dt_obj[key] = val;
});
return {'nb_obj': nb_obj, 'dt_obj': dt_obj'};
};

