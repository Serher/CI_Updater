object Form1: TForm1
  Left = 620
  Top = 376
  BorderStyle = bsSingle
  Caption = #1054#1073#1085#1086#1074#1083#1077#1085#1080#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1099' ConnectionInfo'
  ClientHeight = 120
  ClientWidth = 602
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 56
    Top = 40
    Width = 133
    Height = 13
    Caption = #1054#1073#1085#1086#1074#1083#1077#1085#1080#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1099'...'
  end
  object Memo1: TMemo
    Left = 8
    Top = 168
    Width = 297
    Height = 49
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssBoth
    TabOrder = 0
    Visible = False
    WordWrap = False
  end
  object Memo2: TMemo
    Left = 8
    Top = 224
    Width = 577
    Height = 201
    Lines.Strings = (
      'Memo2')
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object Panel1: TPanel
    Left = 104
    Top = 24
    Width = 393
    Height = 73
    TabOrder = 2
    Visible = False
    object Label1: TLabel
      Left = 1
      Top = 25
      Width = 391
      Height = 13
      Align = alCustom
      Alignment = taCenter
      AutoSize = False
      Caption = #1057#1077#1088#1074#1077#1088' '#1085#1077#1076#1086#1089#1090#1091#1087#1077#1085'... '#1055#1086#1087#1088#1086#1073#1091#1081#1090#1077' '#1087#1086#1079#1078#1077
    end
  end
  object ProgressBar1: TProgressBar
    Left = 56
    Top = 56
    Width = 497
    Height = 17
    Min = 0
    Max = 100
    Smooth = True
    TabOrder = 3
  end
  object OpenDialog1: TOpenDialog
    FileName = 'ConnectionInfo'
    Left = 560
    Top = 168
  end
  object RunDelay: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = RunDelayTimer
    Left = 8
    Top = 8
  end
  object ProgressBarDelay: TTimer
    Enabled = False
    Interval = 400
    OnTimer = ProgressBarDelayTimer
    Left = 8
    Top = 40
  end
  object UpdateDelay: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = UpdateDelayTimer
    Left = 8
    Top = 72
  end
end
