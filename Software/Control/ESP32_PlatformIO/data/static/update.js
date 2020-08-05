<script>
    $('form').submit(function(e){
        e.preventDefault();
        var formId = e.target.id;
        var form = $('#' + formId)[0];
        var data = new FormData(form);
        var targetUrl = e.target.id;

        $.ajax({
            url: targetUrl,
            type: 'POST',
            data: data,
            contentType: false,
            processData: false,
            xhr: function() {
                var xhr = new window.XMLHttpRequest();
                xhr.upload.addEventListener('progress', function(evt) {
                    if (evt.lengthComputable) {
                        var per = evt.loaded / evt.total;
                        //$('#prg').html('progress: ' + Math.round(per*100) + '%');
                        $('#updateProgress').val(Math.round(per*100));
                    }
                }, false);
                return xhr;
            },
            success:function(d, s) {
                console.log('success!')
            },
            error: function (a, b, c) {
            }
        });
    });
</script>

