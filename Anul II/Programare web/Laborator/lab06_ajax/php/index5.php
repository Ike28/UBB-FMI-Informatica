<?php 
    header("Access-Control-Allow-Origin: *");
    function func($mydir, $treePath) {
        echo "<ul>";
        $myfiles = scandir($treePath);

        for ($i = 2; $i < count($myfiles); $i++) {
            $file = $myfiles[$i];
            if ($file != ".git") {
                if (strpos($file, ".")) {
                    echo "<li onclick='fileClicked(this)' value='$treePath'>$file</li><br>";
                }
        
                else {
                    $treePath2 = "$treePath/$file";
                    echo $treePath2 . "<br>";
                    func($file, $treePath2);
                }
            }
        }
        echo "</ul>";
    }

    $treePath = "..";
    func("../", $treePath);
?>
