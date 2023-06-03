var globalPageNumber = 0;

function sendRequest(pageNumber) {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            $("#result").html(this.responseText);
        }
    };

    xmlhttp.open("GET", "php/index2.php?page=" + pageNumber, true);
    xmlhttp.send(null);
}

function previousPage() {
    globalPageNumber--;
    sendRequest(globalPageNumber);
}

function nextPage() {
    globalPageNumber++;
    sendRequest(globalPageNumber);
}
