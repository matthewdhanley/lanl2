<?php
//if($_GET['reset'] == 'reset'){
//    $sendString = $_GET['reset'];
//}
//else {
    if (($_GET['shutter1']=='') || $_GET['shutter2']=='' || $_GET['shutter1']=='') {
        die("ERROR!!!\nYou have an empty field!!!");
    }

    if (($_GET['shutter1'] > 9) || ($_GET['shutter2'] > 9) || ($_GET['shutter3'] > 9)) {
        die("ERROR!!! Not a valid input!!!\nPlease make sure all your values are between 0-9.");
    }

    $sendString = $_GET['shutter1'] . $_GET['shutter2'] . $_GET['shutter3'];
//}
$command = '/usr/bin/python2.7 /home/matt/senior-design/web/sendCode.py '. $sendString; // . $sendString;
exec($command, $out, $rv);
echo("Successfully sent " . $sendString);