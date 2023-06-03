function showArrivals(selectedValue) {
    $("#departure-list").val([]);

    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            $("#result").html(this.responseText);
        }
    };

    xmlhttp.open("GET", "php/index1.php?departure=" + selectedValue, true);
    xmlhttp.send(null);
}
