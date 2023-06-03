function postComment() {

    var id =  $("#title-list option:selected").val();
    var name = $("#name").val();
    var content = $("#content").val();

    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {

        if (this.readyState == 4 && this.status == 200) {

            console.log(this.responseText);

            alert("Comentariul a fost postat cu succes!");
        }
    };

    xmlhttp.open("POST", "index.php");
    xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xmlhttp.send("id=" + id + "&name=" + name + "&content=" + content);
}

function approve() {

    
    var rows = $("#table").find("tr");
    var i = 0;
    rows.each(function() {

        if (i != 0) {

            //var tds = $(this).find("td");

            //var name = $(tds).get(0);
            //var content = tds.get(1);
            //var checked = tds.get(2);

            console.log($(this).find("td")[0]);
        }

        i++;

        /*alert(name);
        alert(content);
        alert(checked);*/
    });

    /*

    .each(function() {

        
        //alert($(this).html());

        var arr = $(this).find("input");

        var name = "";
        var content = "";

        if (arr.length == 0)  {

            name = $(this).html();
            content = $(this).html();
            alert(name);
            alert(content);
        }

        else {

            $(this).find("input").each(function() {

                alert($(this).attr("checked"));
            });
        }

    });*/
}