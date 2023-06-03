var random = Math.floor(Math.random() * 2); // floor of a random number in the interval [0, 2)
var begin;  // h - if human begins; c - else, if computer begins
var game = ['/', '/', '/', '/', '/', '/', '/', '/', '/'];

if (random == 0) {
    begin = 'h';
} else {
    begin = 'c';
    sendRequest(game);
}
console.log(begin);

function writeInCell(cell) {
    console.log(cell);
    $(cell).html("X");
    game[$(cell).attr("id") - 1] = "X";

    var str = game.join(",");
    console.log("After player: ");
    console.log(str);

    sendRequest(str);
}

function sendRequest(gameText) {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);

            if (this.responseText == "humanwin") {
                $("#result").html("Ai castigat!!!");
                alert("Ai castigat!!!");
            } else if (this.responseText == "computerwin") {
                $("#result").html("Computer a castigat :(");
                alert("Computer a castigat :(");
            } else if (this.responseText == "draw") {
                $("#result").html("Remiza");
                alert("Remiza");
            } else {
                var computerPos = (parseInt(this.responseText) + 1).toString();
                console.log("Computer: ");
                console.log(computerPos);

                $("#" + computerPos).html("0");
                game[parseInt(computerPos) - 1] = "0";

                console.log(game.join(","));
            }
        }
    };

    xmlhttp.open("GET", "php/index4.php?game=" + gameText, true);
    xmlhttp.send(null);
}
