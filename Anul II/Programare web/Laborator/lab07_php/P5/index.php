<!DOCTYPE html>
<html>
    <?php 
        function echoForm() {
            echo '<form action="index.php" method="POST" enctype="multipart/form-data">';
            echo 'Selectati imaginea dorita:<br>';
            echo '<input type="file" name="upload" id="upload"><br>';
            echo '<input type="submit" value="Incarcare Imagine" name="submit">';
            $logged = $_COOKIE["logged-in-p5"];
            echo '<input type="hidden" name="u" id="u" value="' . $logged . '">';
            echo '</form>';
        }
    ?>
    <head>
        <title>Problema 5</title>
        <style>
            input {
                margin: 10px;
            }

        </style>
    </head>
    <body>
        <form action="index.php" method="POST">

            Cautare dupa username:<br>
            <input type="text" name="u" id="u"><br>
            <input type="submit" value="Cautare"><br><br>

        </form>

        <?php 
            if (isset($_POST["u"])) {
                $username = $_POST["u"];
                $cookie_username = $_COOKIE["logged-in-p5"];

                if ($username == $cookie_username) {
                    echoForm();
                }
            }
        ?>

        <?php 
            if (isset($_POST["u"])) {
                $username = $_POST["u"];
                $target_dir = "$username/";
                $target_file = null;

                if (array_key_exists("upload", $_FILES)) {
                    $target_file = $target_dir . basename($_FILES["upload"]["name"]);
                }

                $upload_ok = true;
                $errors = "";
                $img_file_type = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));

                if (isset($_POST["submit"])) {
                    $check = getimagesize($_FILES["upload"]["tmp_name"]);

                    if ($check != false) {
                        $upload_ok = true;
                    } else {
                        $upload_ok = false;
                        $errors = $errors . "Fisierul selectat nu este o imagine!\n";
                    }
                }

                if (file_exists($target_file)) {
                    $upload_ok = false;
                    $errors = $errors . "Fisierul selectat exista deja!\n";
                }

                if (!$upload_ok) {
                    echo "<script>alert('$errors');</script>";
                } else {
                    if (!file_exists("$username/")) {
                        mkdir("$username/", 0777, true);
                    }

                    if (array_key_exists("upload", $_FILES)) {
                        if (move_uploaded_file($_FILES["upload"]["tmp_name"], $target_file)) {
                            echo "<script>alert('Fisierul a fost incarcat cu succes!');</script>";
                        } else {
                            echo "<script>alert('Eroare la incarcarea fisierului!);</script>";
                        }
                    }
                }
            }
        ?>

        <?php 
            if (isset($_POST["u"])) {
                $username = $_POST["u"];
                $dir = "$username/";
                $myfiles = scandir($dir);

                echo "<br><br><h3>Imaginile utilizatorului $username:</h3><br><br>";
                for ($i = 2; $i < count($myfiles); $i++) {
                    $img = $myfiles[$i];
                    echo "<img src='$dir$img'><br><br><br>";
                }
            }
        ?>
    </body>
</html>
