var globalModified = false;

function loadListData() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            $("#list").html(this.responseText);
        }
    };

    xmlhttp.open("GET", "php/index3_load.php", true);
    xmlhttp.send(null);
}

function findById(id) {
    var confirmResult = true;
    console.log(globalModified);
    if (globalModified == true) {
        confirmResult = confirm("Sunteti sigur ca doriti sa alegeti alt student?");
    }

    if (confirmResult == true) {
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                console.log(this.responseText);
                $("#form").html(this.responseText);
            }
        };

        xmlhttp.open("GET", "php/index3_find.php?id=" + id, true);
        xmlhttp.send(null);
    }
}

function saveEntry() {
    var id = $("#id-list option:selected").val();
    var nume = $("#nume").val();
    var prenume = $("#prenume").val();
    var telefon = $("#telefon").val();
    var email = $("#email").val();

    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            $("#form").html(this.responseText);
        }
    };

    xmlhttp.open("GET", "php/index3_save.php?id=" + id + "&nume=" + nume + "&prenume=" + prenume + "&telefon=" + telefon + "&email=" + email, true);
    xmlhttp.send(null);
}

function changeFunction() {
    $("#save-button").prop("disabled", false);
    globalModified = true;
}
