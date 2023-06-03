function func() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            $("#result").html(this.responseText);
        }
    };

    xmlhttp.open("GET", "php/index5.php", true);
    xmlhttp.send(null);
}

function fileClicked(listItem) {
    var treePath = $(listItem).attr("value");
    var file = $(listItem).html();
    var str = treePath + "/" + file;

    console.log(treePath);
    console.log(file);

    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            $("#file-content").html(this.responseText);
        }
    };

    xmlhttp.open("GET", "php/index5_file_content.php?file=" + str, true);
    xmlhttp.send(null);
}
