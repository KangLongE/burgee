package com.burgee.study.burgee1;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.io.File;
import java.io.IOException;

import org.springframework.web.bind.annotation.CrossOrigin;

@RestController
@CrossOrigin(origins = "*")

public class CCompilerController {



    @GetMapping("/run")
    public ResponseEntity<String> runExistingCFile() {
        // 절대 경로 사용
        String cFilePath = "C:/burgee/burgee.1/test.c"; // 또는 "C:\\burgee\\test.c" (Windows용)
        String execName = "C:/burgee/burgee.1/test_program"; // 컴파일 결과 실행 파일 경로

        try {
            File cFile = new File(cFilePath);

            // 로그 찍기: 파일 위치와 존재 여부 확인
            System.out.println("C 파일 경로: " + cFile.getAbsolutePath());
            System.out.println("존재하나요?: " + cFile.exists());

            if (!cFile.exists()) {
                return ResponseEntity.badRequest().body("test.c 파일이 없습니다.");
            }

            // gcc로 컴파일
            Process compile = new ProcessBuilder("gcc", cFile.getAbsolutePath(), "-o", execName)
                    .redirectErrorStream(true)
                    .start();
            compile.waitFor();

            String compileOutput = new String(compile.getInputStream().readAllBytes());
            if (compile.exitValue() != 0) {
                return ResponseEntity.badRequest().body("컴파일 오류:\n" + compileOutput);
            }

            // 실행 (Windows에서는 .exe 붙이기)
            String execFile = System.getProperty("os.name").toLowerCase().contains("win")
                    ? execName + ".exe" : execName;

            Process run = new ProcessBuilder(execFile)
                    .redirectErrorStream(true)
                    .start();
            String runOutput = new String(run.getInputStream().readAllBytes());
            run.waitFor();

            return ResponseEntity.ok(runOutput);

        } catch (IOException | InterruptedException e) {
            return ResponseEntity.internalServerError().body("오류 발생: " + e.getMessage());
        }
    }
}