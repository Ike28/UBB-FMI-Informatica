function filterRequest() {
    var crit = $("#crit option:selected").val();
    var keyword = $("#keyword").val();

    console.log(crit);
    console.log(keyword);

    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            $("#table-div").html(this.responseText);
        }
    };

    xmlhttp.open("GET", "php/index6.php?crit=" + crit + "&keyword=" + keyword, true);
    xmlhttp.send(null);
}
