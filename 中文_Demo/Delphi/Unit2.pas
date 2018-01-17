unit Unit2;

interface

uses
  ObjComAuto, Dialogs;

type
  {$METHODINFO ON}
  TScriptableObject = class(TObjectDispatch)
  public
    constructor Create;

    function CZUR_CALLBACK(Count: Integer; httpMsg: WideString;
    file1: WideString; fil2: WideString): HResult;

    function CZUR_UPLOAD_CALLBACK(Success: Integer; fileName: WideString;
    errorCode: Integer; errorMsg: WideString): HResult;

    function CZUR_PDF_CALLBACK(Success: Integer): HResult;

  end;
  {$METHODINFO OFF}

implementation

constructor TScriptableObject.Create;
begin
inherited Create(Self, false);
end;

//拍照回调函数
//Count: http上传文件的个数
//httpMsg: http服务器返回的信息
//file1: 图片文件1的名称，如：D:\1.jpg
//file2: 图片文件2的名称，如：D:\2.jpg
//若设置对拍摄的图片进行上传，Count为上传到http服务器的图片个数，此时，httpMsg为http服务器返回的信息
//针对非拆分双页操作，file2为空
function TScriptableObject.CZUR_CALLBACK(Count: Integer; httpMsg: WideString;
file1: WideString; fil2: WideString): HResult;
begin
//拍照回调只是简单的打印消息，具体处理由用户实现
ShowMessage('拍照回调触发');
Result:=S_OK;
end;

//对本地文件进行http上传结束的回调函数
//Success: http上传文件是否成功，0(上传失败)，1(上传成功)
//fileName: 本地文件名称，如：D:\image.jpg
//errorCode: 错误码
//errorMsg: 错误信息
//若errorCode >= 200，errorMsg为http服务器返回的信息，否则，errorMsg为空
function TScriptableObject.CZUR_UPLOAD_CALLBACK(Success: Integer; fileName: WideString;
errorCode: Integer; errorMsg: WideString): HResult;
begin
//上传回调只是简单的打印消息，具体处理由用户实现
  ShowMessage('上传回调触发');
  Result:= S_OK;
end;

//图片合成pdf结束的回调函数
//Success: 合成pdf的状态，0(合成pdf成功)，1(合成pdf失败)
function TScriptableObject.CZUR_PDF_CALLBACK(Success: Integer): HResult;
begin
//合成pdf回调只是简单的打印消息，具体处理由用户实现
  ShowMessage('合成pdf回调触发');
  Result:= S_OK;
end;

end.
