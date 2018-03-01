var sh = new Shell(true);
sh.exec("am start -a android.intent.action.CALL -d tel:10086");
sh.exit();
