<?php

require_once 'Twig-1.23.3/lib/Twig/Autoloader.php';
Twig_Autoloader::register();

function generate_internal($twig, $in, $out, $args)
{
	$data = $twig->render($in, $args);
	file_put_contents($out, $data);
}

 function rrmdir($dir) { 
   if (is_dir($dir)) { 
     $objects = scandir($dir); 
     foreach ($objects as $object) { 
       if ($object != "." && $object != "..") { 
         if (is_dir($dir."/".$object))
           rrmdir($dir."/".$object);
         else
           unlink($dir."/".$object); 
       } 
     }
     rmdir($dir); 
   } 
 }
 
 
 
function generate($pluginName, $description, $author, $boost, $poco, $openssl, $yadoms){
	try 
	{
		$templateBaseDir = 'templateKit';
		
		$loader = new Twig_Loader_Filesystem($templateBaseDir);
		$twig = new Twig_Environment($loader, array(
			'cache' => 'cache',
		));

		$generationBaseDir = 'generation/';
		$generationDir = $generationBaseDir .  $pluginName;
		
		//remove dir if already exists
		if(file_exists($generationDir) && is_dir($generationDir)) {
			rrmdir($generationDir);
		}
		
		//create folders
		//	pluginName
		//	pluginName/sources
		//	pluginName/sources/locales
		if (!mkdir($generationDir . '/sources/locales', 0777, true)) {
			die('Echec lors de la création des rértoires...');
		}
		
		//apply twig templating		
		$args = array('pluginName' => $pluginName, 'description' => $description, 'author' => $author, 'cppPluginName' => ucfirst($pluginName), 'boost' => $boost, 'poco' => $poco, 'openssl' => $openssl, 'yadoms' => $yadoms);
		generate_internal($twig, 'sources/CMakeLists.tmpl.txt', $generationDir . '/sources/CMakeLists.txt', $args);
		generate_internal($twig, 'sources/Plugin.tmpl.cmake', $generationDir . '/sources/' . $pluginName . '.cmake', $args);
		generate_internal($twig, 'sources/PluginConf.cmake', $generationDir . '/sources/' . $pluginName . 'Conf.cmake', $args);
		generate_internal($twig, 'sources/package.tmpl.json', $generationDir . '/sources/package.json', $args);
		generate_internal($twig, 'sources/locales/en.tmpl.json', $generationDir . '/sources/locales/en.json', $args);
		generate_internal($twig, 'sources/locales/fr.tmpl.json', $generationDir . '/sources/locales/fr.json', $args);
		generate_internal($twig, 'sources/icon.png', $generationDir . '/sources/icon.png', $args);
		generate_internal($twig, 'sources/Plugin.tmpl.h', $generationDir . '/sources/' . $pluginName . '.h', $args);
		generate_internal($twig, 'sources/Plugin.tmpl.cpp', $generationDir . '/sources/' . $pluginName . '.cpp', $args);
		generate_internal($twig, 'sources/Configuration.tmpl.h', $generationDir . '/sources/Configuration.h', $args);
		generate_internal($twig, 'sources/Configuration.tmpl.cpp', $generationDir . '/sources/Configuration.cpp', $args);
		generate_internal($twig, 'sources/stdafx.tmpl.h', $generationDir . '/sources/stdafx.h', $args);
		generate_internal($twig, 'sources/stdafx.tmpl.cpp', $generationDir . '/sources/stdafx.cpp', $args);
		
		//create archive and make it download
		makeArchive($pluginName, $generationBaseDir, $templateBaseDir);
		
		//delete generated plugin folder
		rmmdir($generationDir);
	} catch (Exception $e) {
		$result='<div class="alert alert-danger">Exception : ' . $e->getMessage() .'</div>';
		echo 'Exception <br/>' . nl2br($e->getMessage()) . '<br/>';
		
	}

}

function addToArchive($zip, $folder, $relativeFolder) {
	// Récupération des fichiers.
	  $fichiers = scandir($folder);
	  // On enlève . et .. qui représentent le dossier courant et le dossier parent.
	  unset($fichiers[0], $fichiers[1]);
	  
	  foreach($fichiers as $f)
	  {
		  if(is_dir($folder . '/' . $f)) 
		  {
			if($relativeFolder == '.')
			{
				$zip->addEmptyDir($f); 
				addToArchive($zip, $folder .'/' . $f, $f);
			}
			else
			{
				$zip->addEmptyDir($relativeFolder .'/' .$f); 
				addToArchive($zip, $folder .'/' . $f, $relativeFolder .'/' . $f);
			}
		  }
		  else 
		  {
			// On ajoute chaque fichier à l’archive en spécifiant l’argument optionnel.
			// Pour ne pas créer de dossier dans l’archive.
			if($relativeFolder == '.')
				$res = $zip->addFile($folder . '/' . $f, $f);
			else
				$res = $zip->addFile($folder . '/' . $f, $relativeFolder . '/' . $f);
			
			if(!$res)
			{
				throw new Exception('Cannont add ' . $f . ' to archive.');
			}
		  }
	  }
	
}

function makeArchive($pluginName, $generationBaseDir, $templateBaseDir) {
	$zip = new ZipArchive();
	$filename = $pluginName . '.zip';
	$filepath = $generationBaseDir . '/' . $filename;
	
	if(file_exists($filepath))
		$flags = ZipArchive::OVERWRITE;
	else
		$flags = ZipArchive::CREATE;
	
	if ($zip->open($filepath, $flags)!==TRUE) {
		exit("Impossible d'ouvrir le fichier <$filepath>\n");
	}

	//add generated files
	addToArchive($zip, $generationBaseDir . '/' . $pluginName, '.');
	
	//add static files
	addToArchive($zip, $templateBaseDir . '/static', '.');
	
	$zip->close();
	
	downloadFile($filename, $filepath);
	
	//delete file
	unlink($filepath);
}

function downloadFile($filename, $path) {
  // On peut ensuite, comme dans le tuto de DHKold, proposer le téléchargement.
  header('Content-Transfer-Encoding: binary'); //Transfert en binaire (fichier).
  header('Content-Disposition: attachment; filename="' . $filename . '"'); //Nom du fichier.
  header('Content-Length: '.filesize($path)); //Taille du fichier.
  readfile($path);	
  
  
}

?>