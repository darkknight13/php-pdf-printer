<?php 
interface PDFEngine {
    public function binary($binary);
    public function setOptions($options);
    public function generatePDF();
}

class PDFGenWKHTMLTOPDF implements PDFEngine{
    private $binary = 'wkhtmltopdf';
    private $location = '';
    private $filename = '';
    private $options = array();

    public function __construct($html, $filename, $location, $options = null) {
        $this->html = $html;
        $this->filename = $filename;
        $this->location = $location;
        if (is_array($options)) {
            $this->setOptions($options);
        } 
    }

    public function binary($binary) {
        $this->binary = $binary;
    }

    public function setOptions($options) {
        array_filter($options);
//         $filename = isset($options['filename']) && !empty($options['filename']) ? $options['filename'] : rand(0, 999999);
//         $destination = isset($options['destination']) && !empty($options['destination']) ? $options['destination'] : PDF_SAVE_LOCATION;
//         $attachcss = isset($options['attach_css']) && !empty($options['attach_css']) ? $options['attach_css'] : array();
//         $css = '';
        
        $pdf[] = isset($options['page']) ? '--page-size ' . $options['page'] : '';
        $pdf[] = isset($options['low_quality']) ? '--lowquality' : '';
        $pdf[] = isset($options['orientation']) && ($options['orientation'] == 'Landscape' || $options['orientation'] = 'L') ? '--orientation ' . $options['orientation'] : '';
//         $pdf[] = isset($options['cover']['type']) && isset($options['cover']['content']) && in_array($options['cover']['type'], array(
//             'html', 
//             'file'
//         )) ? 'cover ' . (($options['cover']['type'] == 'html') ? file_unmanaged_save_data($options['cover']['content'], $destination . '/' . $filename . '-cover.html', FILE_EXISTS_REPLACE) : ($options['cover']['type'] == 'file' ? $options['cover']['content'] : '')) : '';
        
        if (isset($options['margin'])) {
            $pdf[] = isset($options['margin']['bottom']) ? '--margin-bottom ' . $options['margin']['bottom'] : '';
            $pdf[] = isset($options['margin']['left']) ? '--margin-left ' . $options['margin']['left'] : '';
            $pdf[] = isset($options['margin']['right']) ? '--margin-right ' . $options['margin']['right'] : '';
            $pdf[] = isset($options['margin']['top']) ? '--margin-top ' . $options['margin']['top'] : '';
        }
//         if (isset($options['skip_bootstrap']) && $options['skip_bootstrap'] == false) {
//             $options['css'][] = array(
//                 'type' => 'url', 
//                 'content' => 'https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css'
//             );
//         }
        
        if (isset($options['header'])) {
            $pdf[] = isset($options['header']['center']) ? '--header-center ' . $options['header']['center'] : '';
            $pdf[] = isset($options['header']['font-name']) ? '--header-font-name ' . $options['header']['font-name'] : '';
            $pdf[] = isset($options['header']['font-size']) ? '--header-font-size ' . $options['header']['font-size'] : '';
            $pdf[] = isset($options['header']['left']) ? '--header-left ' . $options['header']['left'] : '';
            $pdf[] = isset($options['header']['line']) ? '--header-line' : '';
            $pdf[] = isset($options['header']['right']) ? '--header-right ' . $options['header']['right'] : '';
            $pdf[] = isset($options['header']['spacing']) ? '--header-spacing ' . $options['header']['spacing'] : '';
        }
        
        if (isset($options['footer'])) {
            $pdf[] = isset($options['footer']['center']) ? '--footer-center ' . $options['footer']['center'] : '';
            $pdf[] = isset($options['footer']['font-name']) ? '--footer-font-name ' . $options['footer']['font-name'] : '';
            $pdf[] = isset($options['footer']['font-size']) ? '--footer-font-size ' . $options['footer']['font-size'] : '';
            $pdf[] = isset($options['footer']['left']) ? '--footer-left ' . $options['footer']['left'] : '';
            $pdf[] = isset($options['footer']['line']) ? '--footer-line' : '';
            $pdf[] = isset($options['footer']['right']) ? '--footer-right ' . $options['footer']['right'] : '';
            $pdf[] = isset($options['footer']['spacing']) ? '--footer-spacing ' . $options['footer']['spacing'] : '';
        }
        
        $this->options = array_filter($pdf);
    }
    
    public function generatePDF(){
        // using mikehaertl\shellcommand\Command
        $command = new Command($this->binary);
        foreach ($this->options as $options){
            $command->addArg($options);
        }
        $command->addArg($this->html,null,false);
        $command->addArg($this->location.$this->filename.'.pdf');
        echo $command->getExecCommand();
        $command->execute();
    }
}
